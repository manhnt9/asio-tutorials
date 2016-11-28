#include "Network.h"
#include <iostream>

class Server {
public:
  Server(asio::io_service& service);
  ~Server();

  void accept();
  void onNewClient(const std::error_code& e);

  void readHeader();
  void onHeaderRead(const std::error_code& e, const std::size_t bytes);

private:
  asio::ip::tcp::acceptor acceptor_;
  asio::ip::tcp::socket socket_;
  char buffer_[BUFFER_SIZE];
};

Server::Server(asio::io_service& service)
  :  acceptor_(service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8096)),
     socket_(service)
{

}

void Server::accept() {
  acceptor_.async_accept(socket_, std::bind(&Server::onNewClient, this, std::placeholders::_1));
}

void Server::onNewClient(const std::error_code& e) {
  if (!e) {
      std::cout << "New client connected, reading header" << std::endl;
      readHeader();
  } else {
      std::cout << "Connection accept error: " << e.message() << std::endl;
  }
}

void Server::readHeader() {
  asio::async_read(socket_, asio::buffer(buffer_, HEADER_SIZE), 
                   std::bind(&Server::onHeaderRead, this, std::placeholders::_1, std::placeholders::_2));
}

void Server::onHeaderRead(const std::error_code& e, const std::size_t bytes) {
  if (!e) {
      std::cout << "Got header, size: " << bytes << std::endl;
      std::cout << buffer_ << std::endl;
  } else {
      std::cout << "Header read error: " << e.message() << std::endl;
  }
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

