#pragma once

#include "Injector.h"
#include "ProcessInfo.h"
#include "PEreader.h"
#include "PEWrite.h"
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