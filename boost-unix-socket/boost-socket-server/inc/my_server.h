#pragma once

#include <memory>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

class MyServer {
public:
    MyServer();
    ~MyServer();
    void start();
    void stop();
private:
    void startAccept();
    void handleAccept(std::shared_ptr<class Session> connection, const boost::system::error_code& error);
    std::thread m_thread;
    boost::asio::io_service m_ioService;
    boost::asio::local::stream_protocol::acceptor m_acceptor;
};