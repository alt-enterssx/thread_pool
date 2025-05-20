#include <iostream>

#include "./pool_tasker/pool_tasker.h"

int main() {

    PT::pool_task tasker = PT::pool_task(4);
    tasker.add_task(PT::task([](int a, int b, int c) {
        std::cout << a + b + c << std::endl;
    }, 0, 10, 5, 6));

    tasker.add_task(PT::task([]() {
        std::cout << "Hello world" << std::endl;
    }, 1));

    tasker.stop();

    return 0x0;
}
