#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class Task {
public:
    Task();

    virtual ~Task();

    virtual void Run() = 0;  // implemented by subclass
    bool is_running() const { return running; }

    std::string name;
    bool running = false;
};

class ThreadPool {
public:
    explicit ThreadPool(int num_threads);

    ~ThreadPool();

    // Submit a task with a particular name.
    void SubmitTask(const std::string &name, Task *task);
    void remove_task(Task *t);
        
    void WaitForTask(const std::string& name);

    // Stop all threads. All tasks must have been waited for before calling this.
    // You may assume that SubmitTask() is not caled after this is called.
    void Stop();

    void run_thread();

    int num_tasks_unserviced = 0;
private:
    std::mutex mtx;
    std::vector<std::thread *> threads;
    std::vector<Task *> queue;
    volatile bool done = false;

	std::condition_variable cv;
};
