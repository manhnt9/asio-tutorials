#define ASIO_STANDALONE 
#include <asio.hpp>
#include <iostream>

class Client {
    public:
        Client(asio::io_service& service);
        ~Client();

        void connect(const asio::ip::tcp::endpoint& ep);
        void onConnect(const std::error_code& e);

    private:
        asio::ip::tcp::socket socket_;
};

Client::Client(asio::io_service& service) 
    :   socket_(service)
{

}

void Client::connect(const asio::ip::tcp::endpoint& ep) {
    socket_.async_connect(ep, std::bind(&Client::onConnect, this, std::placeholders::_1));
}

void Client::onConnect(const std::error_code& e) {
    std::cout << "Connected to the server" << std::endl; 
}

Client::~Client() {

}

int main() {
    asio::io_service service;
    Client c(service);
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::from_string("127.0.0.1"), 8096);
    c.connect(ep);
    service.run();
    return 0;
}
