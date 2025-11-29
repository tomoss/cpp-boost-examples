#pragma once

#include <vector>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::io_context& ioService);
    ~Session();
    static std::shared_ptr<Session> create(boost::asio::io_context& ioService);
    void start();
    boost::asio::local::stream_protocol::socket& getSocket();
private:
    void readHeader();
    void handleReadHeader(const boost::system::error_code& err, size_t bytes_transferred);
    void readBody(std::size_t length);
    void handleReadBody(const boost::system::error_code& err, size_t bytes_transferred);
    void handleMessage(const std::vector<char>& data);
    boost::asio::local::stream_protocol::socket m_socket;
    uint32_t m_msgLength = 0;
    std::vector<char> m_buffer;
    void closeSocket();
};
