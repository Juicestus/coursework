#include "Step.h"

// Constructor
Step::Step(){
    description = "";
    id = 0;
    duration = 0;
    dependencies = {};
    running = false;
}

// Constructor
Step::Step(int _id, string _desc, int _dur, vector<int> _deps) {
    this->id = _id;
    this->description = _desc;
    this->duration = _dur;
    this->dependencies = _deps;
    this->running = false;
}

Step::~Step() {
    free(t_id);
}

// Removes the dependency from it's dependency list.
void Step::RemoveDep(int _dep) {
    std::vector<int>::iterator pos = find(this->dependencies.begin(), this->dependencies.end(), _dep);
    if (pos != this->dependencies.end()) {
        this->dependencies.erase(pos);
    }
}

// Print that the step is complete.
void Step::PrintComplete() {
    cout << "Completed Step: " << this->id << " - " << this->description << endl;
}

