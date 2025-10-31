#include "StepList.h"

// Parses the given file for steps and add them to the stepList vector.
StepList::StepList(string file) {
	stepList = extractStepInfo(file);
}

StepList::~StepList() {
	for(int i=0; i<(int)stepList.size(); i++) {
		delete stepList[i];
	}
}

vector<int> StepList::splitString(string str, char splitter) {
    vector<int> result;
    string current = ""; 
    for(size_t i = 0; i < str.size(); i++){
        if(str[i] == splitter){
            if(current != ""){
                result.push_back(stoi(current));
                current = "";
            } 
            continue;
        }
        current += str[i];
    }
    if(current.size() != 0)
        result.push_back(stoi(current));
    return result;
}

vector<Step*> StepList::extractStepInfo(string file) {
	vector<Step*> result;
	ifstream processFile (file);
	if (!processFile.is_open()) {
		perror("could not open file");
		exit(1);
	}

	// read contents and populate process_info vector
	string curr_line, temp_num;
	int curr_id;
	string curr_desc;
	vector<int> curr_deps;
	int curr_dur;

	// Burn header line
	getline(processFile, curr_line);
	while (getline(processFile, curr_line)) {
		// use string stream to seperate by comma
		curr_deps.clear();
		stringstream ss(curr_line);

		// ID
		getline(ss, temp_num, ',');
		curr_id = stoi(temp_num);
		// Dependencies
		getline(ss, temp_num, ',');
		curr_deps = splitString(temp_num, ' ');
		// Duration
		getline(ss, temp_num, ',');
		curr_dur = stoi(temp_num);
		// Description
		getline(ss, curr_desc, ',');

		Step* p = new Step(curr_id, curr_desc, curr_dur, curr_deps);
		result.push_back(p);
	}

	// close file
	processFile.close();
	return result;
}

int StepList::Count() {
	return (int)stepList.size();
}

// Returns all steps that are ready to be started, the dependency list is empty.
vector<Step*> StepList::GetReadySteps() {
	vector<Step*> result;
	for(Step* item : stepList) {
		if(!item->running && item->dependencies.empty()) {
			cout << "Step " << item->id << " ready to be run." << endl;
			result.push_back(item);
		}
	}
	return result;
}

// Remove the given dependency from the dep list.
void StepList::RemoveDependency(int dep) {
	for(Step* item : stepList) {
		item->RemoveDep(dep);
	}
}