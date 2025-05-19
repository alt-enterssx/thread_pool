//  -----------------------------
//  ▐ Bag report
//  -----------------------------

#ifndef POOL_TASKER_H
#define POOL_TASKER_H

//  -----------------------------
//  ▐ Includes
//  -----------------------------

#include <cstdint>
#include <functional>
#include <utility>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <deque>
#include <vector>

//  -----------------------------
//  ▐ Usings
//  -----------------------------

using namespace std;

//  -----------------------------
//  ▐ Full code of pool tasker
//  -----------------------------

namespace PT {

    //  ▐ Status of task completed
    enum task_status {
        complete = 0x0,
        in_queue = 0x1
    };

    //  ▐ Task class
    class task {

        public:
            //  ▐ Constructor and Desctructor
            template<typename F, typename ...Args>
            task(F&& f, uint8_t id, Args&& ...args) : status(task_status::in_queue), id(id) {
                if (f != nullptr) {
                    this->executor = [func = std::forward<F>(f), ...args_frd = std::forward<Args>(args)]() mutable -> void {
                        func(std::forward<decltype(args_frd)>(args_frd)...);
                    };
                }
            }
            
            task();
            
            ~task() noexcept;

            //  ▐ Id functions
            void set_id(uint8_t id) noexcept;
            uint8_t get_id() noexcept;

            //  ▐ Other functions
            void execute() noexcept;
            PT::task_status get_status() noexcept;

        private:
            //  ▐ Params of task
            uint8_t id;
            PT::task_status status;

            function<void()> executor;

    };

    //  ▐ Pool task class
    class pool_task {

        public:
            //  ▐ Constructor and Destructor
            pool_task(int threads_cnt) noexcept;

            ~pool_task() noexcept;

            //  ▐ Add task to pool
            void add_task(PT::task&& task);

            //  ▐ Wait all threads
            void wait() noexcept;

            //  ▐ Stop and shutdown all threads
            void stop() noexcept;

        private:
            //  ▐ Params of pool task
            vector<thread> threads;
            deque<PT::task> tasks;

            mutex mtx;
            condition_variable cv;
            bool stop_fg;

    };

}

#endif