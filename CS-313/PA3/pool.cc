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
    std::lock_guard<std::mutex> lock(mtx);
    for (Task *q : queue) {
        delete q;
    }
    queue.clear();
}

void ThreadPool::SubmitTask(const std::string &name, Task *task) {
    std::unique_lock<std::mutex> lock(mtx);

       if (done) {
        return;
    }

    task->name = name;
    task->running = false;

    queue.push_back(task);
    num_tasks_unserviced++;
    cv.notify_one();
}

void ThreadPool::run_thread() {
    while (true) {
        Task *task = nullptr;

        {
            std::unique_lock<std::mutex> lock(mtx);

            cv.wait(lock, [this]() {
                return done || !queue.empty();
            });

            if (done && queue.empty()) {
                return;
            }

            if (!queue.empty()) {
                task = queue.front();
                queue.erase(queue.begin());
                if (task) {
                    task->running = true;
                }
            }
        }

        if (!task) {
            continue;
        }

        std::cout << "Started task \"" << task->name
                  << "\" on thread " << std::this_thread::get_id()
                  << std::endl;

        task->Run();

        {
            std::unique_lock<std::mutex> lock(mtx);
            task->running = false;
            num_tasks_unserviced--;
        }

        delete task;
    }
}

void ThreadPool::remove_task(Task *t) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        if (*it == t) {
            queue.erase(it);

            num_tasks_unserviced--;

            delete t;
            return;
        }
    }
}

void ThreadPool::Stop() {
    {
        std::unique_lock<std::mutex> lock(mtx);

        if (done) {
            return;
        }

        done = true;
        cv.notify_all();
    }

    for (std::thread *t : threads) {
        if (t && t->joinable()) {
            t->join();
        }
        delete t;
    }
    threads.clear();
}