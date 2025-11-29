#pragma once

#include <functional>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio.hpp>

class Timer {
public:
    using TimeoutEventHandler_t = std::function<void()>;

    Timer(TimeoutEventHandler_t p_handler, boost::asio::io_context& p_ioContext);
    ~Timer();

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&& other) = delete;
    Timer& operator=(Timer&& other) = delete;
    
    void start(unsigned int p_timeoutMs);
    void cancel();
private:
    boost::asio::steady_timer m_timer;
    TimeoutEventHandler_t m_handler;
};