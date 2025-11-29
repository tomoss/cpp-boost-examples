#include "session.h"
#include "gps_position.pb.h"

#include <iostream>
#include <arpa/inet.h> // For ntohl

Session::Session(boost::asio::io_service& ioService) : m_socket(ioService) {

}

Session::~Session() {
    closeSocket();
}

std::shared_ptr<Session> Session::create(boost::asio::io_service& ioService) {
    return std::make_shared<Session>(ioService);
}

void Session::start() {
    readHeader();
}

void Session::readHeader() {
    auto self = shared_from_this();

    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(&m_msgLength, sizeof(m_msgLength)),
        [this, self](const boost::system::error_code& error, std::size_t bytes_transferred) {
            self->handleReadHeader(error, bytes_transferred);
        }
    );
}

void Session::handleReadHeader(const boost::system::error_code& err, size_t bytes_transferred) {
    if (err) {
        if (err == boost::asio::error::eof) {
            std::cout << "Client disconnected." << std::endl;
        } else {
            std::cerr << "Header read error: " << err.message() << std::endl;
        }
        closeSocket();
        return;
    }

    if (bytes_transferred != sizeof(m_msgLength)) {
        std::cerr << "Incomplete header read" << std::endl;
        closeSocket();
        return;
    }

    m_msgLength = ntohl(m_msgLength); // Convert from network byte order to host byte order
    readBody(m_msgLength);    
}

void Session::readBody(std::size_t length) {
    m_buffer.resize(length);
    auto self = shared_from_this();

    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(m_buffer.data(), m_buffer.size()),
        [this, self](const boost::system::error_code& error, std::size_t bytes_transferred) {
            self->handleReadBody(error, bytes_transferred);
        }
    );
}
    

void Session::handleReadBody(const boost::system::error_code& err, size_t bytes_transferred) {
    if (err) {
        std::cerr << "Body read error: " << err.message() << std::endl;
        closeSocket();
        return;
    }

    if (bytes_transferred != m_buffer.size()) {
        std::cerr << "Incomplete body read" << std::endl;
        closeSocket();
        return;
    }

    handleMessage(m_buffer);    
}

void Session::handleMessage(const std::vector<char>& data) {
    messages::GPSPositionMessage msg;

    if (!msg.ParseFromArray(data.data(), data.size())) {
        std::cerr << "Failed to parse GPS message\n";
        return;
    }
    
    std::cout << "[Server] GPS: "
              << "lat=" << msg.latitude()
              << " lon=" << msg.longitude()
              << " alt=" << msg.altitude()
              << std::endl;

    // Continue reading more messages from this connection
    readHeader();
}

boost::asio::local::stream_protocol::socket& Session::getSocket() {
    return m_socket;
}

void Session::closeSocket() {
    if (m_socket.is_open()) {
        boost::system::error_code ec;
        m_socket.close(ec);
        if (ec) {
            std::cerr << "Error closing socket: " << ec.message() << std::endl;
        }
    }
}