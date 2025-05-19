//  ▐ Include .h file

#include "./pool_tasker.h"

//  -----------------------------
//  ▐ Realisation task class
//  -----------------------------

PT::task::task()
    : status(PT::task_status::in_queue), id(static_cast<uint8_t>(-1)) {}

PT::task::~task() noexcept {
    this->status = PT::task_status::complete;
    this->executor = nullptr;
}

void PT::task::set_id(uint8_t id) noexcept {
    this->id = id;
}

uint8_t PT::task::get_id() noexcept {
    return this->id;
}

void PT::task::execute() noexcept {
    if (this->executor) {
        this->executor();
        this->status = PT::task_status::complete;
    }
}

PT::task_status PT::task::get_status() noexcept {
    return this->status;
}

//  -----------------------------
//  ▐ Realisation pool_task class
//  -----------------------------

PT::pool_task::pool_task(int threads_cnt) noexcept
    : stop_fg(false) {
    for (int i = 0; i < threads_cnt; i++) {
        this->threads.emplace_back([this]() {
            while (true) {
                PT::task task_to_run;

                {
                    std::unique_lock<std::mutex> lk(this->mtx);
                    this->cv.wait(lk, [this]() {
                        return !this->tasks.empty() || this->stop_fg;
                    });

                    if (this->stop_fg && this->tasks.empty()) {
                        return;
                    }

                    task_to_run = std::move(this->tasks.back());
                    this->tasks.pop_back();
                }

                task_to_run.execute();
            }
        });
    }
}

PT::pool_task::~pool_task() noexcept {
    this->stop();
}

void PT::pool_task::add_task(PT::task&& task) {
    {
        std::lock_guard<std::mutex> lg(this->mtx);
        this->tasks.push_front(std::move(task));
    }

    this->cv.notify_one();
}

void PT::pool_task::wait() noexcept {
    for (std::thread& t : this->threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void PT::pool_task::stop() noexcept {
    {
        std::lock_guard<std::mutex> lg(this->mtx);
        this->stop_fg = true;
    }

    this->cv.notify_all();

    for (std::thread& t : this->threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
