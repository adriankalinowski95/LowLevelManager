#pragma once
#include "MainController.h"
//#include <vector>

class InjectShellcodeController
{
public:
	InjectShellcodeController();
	~InjectShellcodeController();
	void injectBytesShellcode(const char* shellcode);
	bool injectAsmShellcode(const char* shellcode);

};

