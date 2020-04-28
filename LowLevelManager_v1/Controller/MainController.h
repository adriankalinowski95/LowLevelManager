#pragma once

#include "Service/Injector.h"
#include "Service/ProcessInfo.h"
#include "Service/PEreader.h"
#include "Service/PEWrite.h"
#include <windows.h>
#include "distorm.h"



class MainController
{

	public:
		MainController();
		~MainController();
		Injector* getInjector();
		void getProcessList();
		ProcessInfo* getProcessInformation();
		PEWrite* getPEWrtie();
		PEReader* getPEReader();
		HANDLE loadProcessByName(LPWSTR processName);
		bool loadProcessByPID(DWORD pid);
		int getInstructions(LPCVOID startAddress, _DecodedInst instructions[], int byteSize);
		int getInstructionsByIndex(LPCVOID startAddress, _DecodedInst instructions[], unsigned long startIndex, int instructionCount);
		unsigned long getInstructionIndex(LPCVOID startAddress, LPCVOID instructionAddress);
		
	private:
		Injector* processInjector;
		ProcessInfo* processInformation;
		PEReader* processReader;
		PEWrite* processWriter;

};