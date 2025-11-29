#include "timer.h"
#include <iostream>
#include <utility>

Timer::Timer(TimeoutEventHandler_t p_handler, boost::asio::io_context& p_ioContext) :
    m_timer(p_ioContext),
    m_handler(std::move(p_handler))
{

}

void Timer::start(unsigned int p_timeoutMs) {
        m_timer.cancel();  // Cancel any existing timer
        m_timer.expires_after(std::chrono::milliseconds(p_timeoutMs));

        m_timer.async_wait([this](const boost::system::error_code& error) {
            if (error) {
                if (error == boost::asio::error::operation_aborted) {
                    // Timer was canceled, no action needed
                    return;
                } else {
                    std::cerr << "Timer error: " << error.message() << std::endl;
                    return;
                }
            }

            if (!m_handler) {
                std::cerr << "Timer has no handler!" << std::endl;
                return;
            }

            try {
                m_handler();
            } catch (const std::exception& ex) {
                std::cerr << "Timer handler threw exception: " << ex.what() << std::endl;
            } catch (...) {
                std::cerr << "Timer handler threw unknown exception" << std::endl;
            }
        });
}

void Timer::cancel() {
    try {
        m_timer.cancel();
    } catch (boost::system::system_error& error) {
        std::cerr << "Failed to cancel timer: " << error.code().message() << std::endl;
    }
}

Timer::~Timer() {
    try {
        m_timer.cancel();
    } catch (boost::system::system_error& error) {
        std::cerr << "Failed to cancel timer in destructor: " << error.code().message() << std::endl;
    }
}



