#ifndef STEPLIST_HEADER
#define STEPLIST_HEADER
#include <sstream>
#include <fstream>
#include <tuple>
#include <memory>
#include <queue>
#include <cassert>
#include "Step.h"

class StepList {
	vector<int> splitString(string str, char splitter);
	vector<Step*> extractStepInfo(string file);
	vector<Step*> stepList;
public:
	StepList(string file);
	~StepList();
	vector<Step*> GetReadySteps();
	void RemoveDependency(int dep);
	int Count();
};



#endif