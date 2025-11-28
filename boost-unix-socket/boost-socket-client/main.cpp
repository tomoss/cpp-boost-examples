#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <arpa/inet.h> // For ntohl and htonl
#include <google/protobuf/stubs/common.h>
#include "gps_position.pb.h"

static constexpr std::string_view SOCKET_PATH = "/tmp/test_server";

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    std::cout << "Starting client app..." << std::endl;

    boost::asio::io_service ioService;
    boost::asio::local::stream_protocol::socket socket(ioService);
    boost::asio::local::stream_protocol::endpoint endpoint(SOCKET_PATH.data());
    socket.connect(endpoint);

    messages::GPSPositionMessage gpsMessage;
    gpsMessage.set_latitude(37.7749);
    gpsMessage.set_longitude(-122.4194);
    gpsMessage.set_altitude(30.0);

    std::string serializedData;
    if (!gpsMessage.SerializeToString(&serializedData)) {
        std::cerr << "Failed to serialize GPSPositionMessage." << std::endl;
        return 1;
    }

    // Length prefix
    uint32_t len = serializedData.size();
    uint32_t len_be = htonl(len);

    // Send length
    boost::asio::write(socket, boost::asio::buffer(&len_be, sizeof(len_be)));
    // Send payload
    boost::asio::write(socket, boost::asio::buffer(serializedData));

    std::cout << "Message sent (" << len << " bytes)." << std::endl;
}