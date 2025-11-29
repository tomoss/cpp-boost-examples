#include <iostream>
#include <csignal>
#include <atomic>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <google/protobuf/stubs/common.h>
#include "my_server.h"

std::atomic<bool> shutdownRequested(false);

void signalHandler(int signum) {
    shutdownRequested.store(true);
}

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    std::signal(SIGINT,  signalHandler);
    std::signal(SIGTERM, signalHandler);

    std::cout << "Starting Server app..." << std::endl;
    MyServer server;
    server.start();
    while (!shutdownRequested.load()) {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    }
}