#pragma once

#include <memory>
#include <thread>
#include <boost/asio.hpp>

class Session;

class MyServer {
public:
    MyServer();
    ~MyServer();
    void start();
    void stop();
private:
    void startAccept();
    void handleAccept(std::shared_ptr<Session> connection, const boost::system::error_code& error);
    std::thread m_thread;
    boost::asio::io_service m_ioService;
    boost::asio::local::stream_protocol::acceptor m_acceptor;
};