#include <iostream>

#include "asio.hpp"

#include "CHIRP/BroadcastRecv.hpp"

using namespace cnstln::CHIRP;

int main(int argc, char* argv[]) {
    // Specify any address via cmdline
    asio::ip::address any_address {};
    if(argc < 2) {
        any_address = asio::ip::address_v4::broadcast();
    }
    else if (argc == 2) {
        any_address = asio::ip::make_address(argv[1]);
    }
    else {
        return 1;
    }

    asio::io_context io_context {};
    BroadcastRecv receiver {io_context, any_address};

    while(true) {
        auto message = receiver.RecvBroadcast();
        std::cout << "recv message from " << message.ip.to_string() << ": " << message.content_to_string() << std::endl;
    }

    return 0;
}