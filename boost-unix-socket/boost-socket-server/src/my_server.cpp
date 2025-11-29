#include <iostream>
#include "my_server.h"
#include "session.h"

static constexpr std::string_view SOCKET_PATH = "/tmp/test_server";

MyServer::MyServer() : 
    m_ioService(),
    m_acceptor(m_ioService, boost::asio::local::stream_protocol::endpoint(SOCKET_PATH.data())) {
    
}

MyServer::~MyServer() {
    stop();
}

void MyServer::startAccept() {
    auto session = Session::create(m_ioService);

    m_acceptor.async_accept(
        session->getSocket(),
        [this, session](const boost::system::error_code& error) {
            handleAccept(session, error);
        }
    );
}

void MyServer::handleAccept(std::shared_ptr<Session> session, const boost::system::error_code& error) {
    if (!error) {
        session->start();
    } else {
        std::cerr << "Accept error: " << error.message() << std::endl;
    }
    startAccept();
}

void MyServer::start() {
    startAccept();
    m_thread = std::thread([this]() {
        m_ioService.run();
    });
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