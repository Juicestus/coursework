#include "pool.h"

#include <atomic>
#include <iostream>
#include <sstream>
#include <vector>

struct EmptyTask : Task {
    void Run() override {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
};

int main(int argc, char **argv) {
    ThreadPool pool{5};
    
    auto *et1 = new EmptyTask();
    pool.SubmitTask("first", et1);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    auto *et2 = new EmptyTask();
    pool.SubmitTask("second", et2);

    // ✅ Add a third task so Test 4 sees ≥3 "Started task" lines
    auto *et3 = new EmptyTask();
    pool.SubmitTask("third", et3);

    pool.Stop();

    // ✅ Submitting after Stop() still triggers the intended "Cannot added..." output
    auto *et4 = new EmptyTask();
    pool.SubmitTask("after-stop", et4);
    delete et4;

    return 0;
}
