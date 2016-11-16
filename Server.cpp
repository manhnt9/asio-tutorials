#define ASIO_STANDALONE
#include <asio.hpp>
#include <iostream>

class Server {
    public:
        Server(asio::io_service& service);
        ~Server();

        void accept();
        void onNewClient(const std::error_code& e);

    private:
        asio::ip::tcp::acceptor acceptor_;
        asio::ip::tcp::socket socket_;
};

Server::Server(asio::io_service& service)
    :   acceptor_(service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8096)),
        socket_(service)
{

}

void Server::accept() {
    acceptor_.async_accept(socket_, std::bind(&Server::onNewClient, this, std::placeholders::_1));
}

void Server::onNewClient(const std::error_code& e) {
    std::cout << "New client connected" << std::endl;
}

Server::~Server() {

}

int main() {
    asio::io_service service;
    Server s(service);
    s.accept();
    service.run();
    return 0;
}

