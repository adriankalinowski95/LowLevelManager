#pragma once
#include "MainController.h"
#include <vector>

#define MAX_CHAR_ARRAY 500

struct CharInformationStruct {
	char information[MAX_CHAR_ARRAY];
	char value[MAX_CHAR_ARRAY];
};

class InformationProcessController
{

public:
	InformationProcessController(MainController* mainController);
	bool getInfromation(std::vector<CharInformationStruct>* processInfo);
	~InformationProcessController();

private:
	MainController* mainController;
};

