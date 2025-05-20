🧵 pool_tasker
A lightweight multithreaded task pool in C++ with minimal dependencies. It supports deferred task execution and automatic thread management using a work queue.

📌 Features
Simple integration

Deferred task execution

Automatic thread pool management

Thread-safe task queue

Wait for all threads to finish

Controlled shutdown of the thread pool

⚙️ Usage
Include the Header
cpp
Копировать
Редактировать
#include "pool_tasker.h"
Create a Task Pool
cpp
Копировать
Редактировать
PT::pool_task pool(4); // Create a thread pool with 4 threads
Add Tasks
cpp
Копировать
Редактировать
pool.add_task(PT::task([](int a, int b) {
    std::cout << "Sum: " << a + b << std::endl;
}, 1, 5, 10));
Wait for Completion
cpp
Копировать
Редактировать
pool.wait(); // Blocks until all threads complete their execution
Stop the Pool
cpp
Копировать
Редактировать
pool.stop(); // Gracefully stops the thread pool
📦 Classes Overview
PT::task
Encapsulates a unit of work with an identifier.

Constructor:

cpp
Копировать
Редактировать
template<typename F, typename... Args>
task(F&& f, uint8_t id, Args&&... args);
Methods:

void set_id(uint8_t id) noexcept;

uint8_t get_id() noexcept;

void execute() noexcept;

task_status get_status() noexcept;

PT::pool_task
Manages worker threads and a task queue.

Constructor:

cpp
Копировать
Редактировать
pool_task(int thread_count) noexcept;
Methods:

void add_task(PT::task&& task);

void wait() noexcept;

void stop() noexcept;

🧪 Example
cpp
Копировать
Редактировать
#include "pool_tasker.h"
#include <iostream>

int main() {
    PT::pool_task pool(2);

    for (int i = 0; i < 5; ++i) {
        pool.add_task(PT::task([](int id) {
            std::cout << "Task " << id << " is running\n";
        }, i, i));
    }

    pool.wait();
    return 0;
}
📄 License
MIT License. Feel free to use and modify.
