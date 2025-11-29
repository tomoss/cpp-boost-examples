#include <iostream>

#include "timer_manager.h"
#include "timer.h"

TimerManager::TimerManager() : 
    m_ioContext(),
    m_workGuard(boost::asio::make_work_guard(m_ioContext))
{
    m_thread = std::thread([this]() {
        m_ioContext.run();
    });
}

TimerManager::~TimerManager() {
    clear();
    if (m_ioContext.stopped() == false) {
        m_workGuard.reset();
        m_ioContext.stop();
    }
    if (m_thread.joinable()) {
        m_thread.join();
    }
    std::cout << "TimerManager destroyed" << std::endl;
}

uint64_t TimerManager::addTimer(Timer::TimeoutEventHandler_t p_handler) {
    uint64_t timerId = m_nextTimerId++;
    auto timer = std::make_shared<Timer>(std::move(p_handler), m_ioContext);
    m_timers.emplace(timerId, std::move(timer));
    return timerId;
}

void TimerManager::startTimer(uint64_t p_timerId, unsigned int p_timeoutMs) {
    auto timer = getTimer(p_timerId);
    if (!timer) {
        std::cout << "Timer with ID " << p_timerId << " not found" << std::endl;
    } else {
        timer->start(p_timeoutMs);
        std::cout << "Started timer with ID " << p_timerId << " for " << p_timeoutMs << " ms" << std::endl;
    }
}

void TimerManager::cancelTimer(uint64_t timerId) {
    auto timer = getTimer(timerId);
    if (!timer) {
        std::cout << "Timer with ID " << timerId << " not found for cancellation" << std::endl;
    } else {
        timer->cancel();
        std::cout << "Canceled timer with ID " << timerId << std::endl;
    }
}

void TimerManager::removeTimer(uint64_t timerId) {
    auto it = m_timers.find(timerId);
    if (it != m_timers.end()) {
        it->second->cancel();
        m_timers.erase(it);
        std::cout << "Removed timer with ID " << timerId << std::endl;
    } else {
        std::cout << "Timer with ID " << timerId << " not found for removal" << std::endl;
    }
}

std::shared_ptr<Timer> TimerManager::getTimer(uint64_t timerId) {
    auto it = m_timers.find(timerId);
    if (it == m_timers.end()) {
        return nullptr;
    } else {
        return it->second;
    }
}

void TimerManager::clear() {
    for (auto& pair : m_timers) {
        pair.second->cancel();
    }
    m_timers.clear();
}
