#pragma once

#include <vector>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

class ConnHandler : public boost::enable_shared_from_this<ConnHandler> {
public:
    ConnHandler(boost::asio::io_service& ioService);
    ~ConnHandler() = default;
    static boost::shared_ptr<ConnHandler> create(boost::asio::io_service& ioService);
    void start();

    void readHeader();
    void handleReadHeader(const boost::system::error_code& err, size_t bytes_transferred);

    void readBody(std::size_t length);
    void handleReadBody(const boost::system::error_code& err, size_t bytes_transferred);

    void handleMessage(const std::vector<char>& data);

    boost::asio::local::stream_protocol::socket& getSocket();
private:
    boost::asio::local::stream_protocol::socket m_socket;
    uint32_t m_msgLength = 0;
    std::vector<char> m_buffer;
};
