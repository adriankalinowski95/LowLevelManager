#pragma once
#include "MainController.h"
#include <vector>

#define MAX_CHAR_ARRAY 500

struct CharProcessStruct {
	char processName[MAX_CHAR_ARRAY];
	char processPID[MAX_CHAR_ARRAY];
};


 class OpenProcessController
{
public:
	OpenProcessController(MainController* mainController);
	~OpenProcessController();
	bool loadProcess(std::vector< CharProcessStruct>* processes);
	bool selectProcess(int index);

private:
	MainController* mainController;
	std::vector<ProcessStruct>* processVector;
};

