#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread.hpp>

class MyServer {
public:
    MyServer();
    ~MyServer();
    void start();
    void stop();
private:
    void startAccept();
    void handleAccept(boost::shared_ptr<class ConnHandler> connection, const boost::system::error_code& error);
    boost::thread m_thread;
    boost::asio::io_service m_ioService;
    boost::asio::local::stream_protocol::acceptor m_acceptor;
};