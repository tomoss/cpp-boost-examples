#include <iostream>
#include "timer_manager.h"

std::atomic<bool> shutdownRequested(false);

void signalHandler(int signum) {
    shutdownRequested.store(true);
}

int main() {
    std::signal(SIGINT,  signalHandler);
    std::signal(SIGTERM, signalHandler);

    std::cout << "Starting app..." << std::endl;
    TimerManager timerManager;
    try {
        uint64_t timer1 = timerManager.addTimer([]() {
            std::cout << "Timer 1 expired!" << std::endl;
        });

        uint64_t timer2 = timerManager.addTimer([]() {
            std::cout << "Timer 2 expired!" << std::endl;
        });

        timerManager.startTimer(timer1, 2000); // 2 seconds

        timerManager.startTimer(timer2, 10000);

        timerManager.cancelTimer(timer2);
        timerManager.removeTimer(timer2);
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    while (!shutdownRequested.load()) {
            sleep(100);
    }
}