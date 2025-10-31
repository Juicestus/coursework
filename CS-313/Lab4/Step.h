#ifndef STEP_HEADER
#define STEP_HEADER
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Step{
public:
	timer_t t_id;
	string description;
	int id;
	int duration;
	bool running;
	vector<int> dependencies;
	Step();
	Step(int _id, string _desc, int _dur, vector<int> _deps);
	~Step();
	void RemoveDep(int _dep);
	void PrintComplete();
};

#endif