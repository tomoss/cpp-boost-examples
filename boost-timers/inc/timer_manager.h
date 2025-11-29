#pragma once
#include <thread>
#include <unordered_map>
#include <memory>
#include <boost/asio.hpp>

#include "timer.h"

class TimerManager {
public:
    TimerManager();
    ~TimerManager();

    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;

    uint64_t addTimer(Timer::TimeoutEventHandler_t p_handler);
    void startTimer(uint64_t p_timerId, unsigned int p_timeoutMs);
    void cancelTimer(uint64_t timerId);
    void removeTimer(uint64_t timerId);
    void clear();  // Cancel and remove all

private:
    std::shared_ptr<Timer> getTimer(uint64_t timerId);
    std::thread m_thread;
    uint64_t m_nextTimerId{1};
    boost::asio::io_context m_ioContext;
    std::unordered_map<uint64_t, std::shared_ptr<Timer>> m_timers;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workGuard;

};