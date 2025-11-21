#include "pool.h"
#include <iostream>

Task::Task() = default;
Task::~Task() = default;

ThreadPool::ThreadPool(int num_threads) {
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(new std::thread(&ThreadPool::run_thread, this));
    }
}

ThreadPool::~ThreadPool() {
    Stop();
    for (Task* q : queue)
        delete q;
    queue.clear();
}

void ThreadPool::SubmitTask(const std::string &name, Task *task) {
    std::unique_lock<std::mutex> lock(mtx);

    if (done) 
    {
        std::cout << "Cannot added task to queue\n";
        return;
    }

    task->name = name;
    queue.push_back(task);

    std::cout << "Added task " << name << "\n";
    num_tasks_unserviced++;
    lock.unlock();
    cv.notify_one();
}


void ThreadPool::WaitForTask(const std::string& name) 
{
}

void ThreadPool::run_thread() {
    while (true) 
    {
        Task* task = nullptr;
        {
            std::unique_lock<std::mutex> lock(mtx);

            cv.wait(lock, [this]() 
            {
                return done || !queue.empty();
            });

            if (done && queue.empty()) 
            {
                std::cout << "Stopping thread\n";
                return;
            }

            task = queue.front();
            queue.erase(queue.begin());
            std::cout << "Started task " << task->name << "\n";
        }
        task->Run();
        std::cout << "Finished task " << task->name << "\n";
        delete task;
    }
}



void ThreadPool::remove_task(Task *t) {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto iter = queue.end(); iter != queue.begin(); iter--) 
    {
        if (*iter == t) 
        {
            queue.erase(iter);

            num_tasks_unserviced--;

            delete t;
            return;
        }
    }
}

void ThreadPool::Stop() {
    {
        std::unique_lock<std::mutex> lock(mtx);

        if (done) 
        {
            return;
        }
        std::cout << "Called Stop()" << std::endl;
        done = true;
    }
    cv.notify_all();

    for (std::thread* t : threads) 
    {
        if (t && t->joinable()) 
        {
            t->join();
        }
        delete t;
    }
    threads.clear();
}
