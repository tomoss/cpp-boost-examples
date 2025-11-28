#include <iostream>
#include "my_server.h"
#include "conn_handler.h"

static constexpr std::string_view SOCKET_PATH = "/tmp/test_server";

MyServer::MyServer() : m_ioService(), m_acceptor(m_ioService, boost::asio::local::stream_protocol::endpoint(SOCKET_PATH.data()))
{
    
}

MyServer::~MyServer() {
    stop();
}

void MyServer::startAccept() {
    boost::shared_ptr<ConnHandler> connection = ConnHandler::create(m_ioService);
    m_acceptor.async_accept(connection->getSocket(),
        boost::bind(&MyServer::handleAccept, this, connection,
          boost::asio::placeholders::error));
}

void MyServer::handleAccept(boost::shared_ptr<ConnHandler> connection, const boost::system::error_code& error) {
    if (!error) {
        connection->start();
    } else {
        std::cerr << "Accept error: " << error.message() << std::endl;
    }
    startAccept();
}

void MyServer::start() {
    startAccept();
    m_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_ioService));
    std::cout << "Server started, listening on " << SOCKET_PATH << std::endl;
}

void MyServer::stop() {
    if (m_ioService.stopped() == false) {
        m_ioService.stop();
    }
    if (m_thread.joinable()) {
        m_thread.join();
    }
    ::unlink(SOCKET_PATH.data());

    std::cout << "Server stopped." << std::endl;
}