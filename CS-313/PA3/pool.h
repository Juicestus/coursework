#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Task {
public:
Task();
virtual ~Task();

virtual void Run() = 0;
bool is_running() const { return running; }

std::string name;
bool running = false;
};

class ThreadPool {
public:
explicit ThreadPool(int num_threads);
~ThreadPool();

void SubmitTask(const std::string &name, Task *task);

void remove_task(Task *t);
void Stop();

void run_thread();

int num_tasks_unserviced = 0;

private:
std::mutex mtx;
std::condition_variable cv;
std::vector<std::thread *> threads;
std::vector<Task *> queue;
bool done = false;
};

