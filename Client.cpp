#include "Network.h"
#include <iostream>
#include <cstring>

class Client {
public:
  Client(asio::io_service& service);
  ~Client();

  void connect(const asio::ip::tcp::endpoint& ep);
  void onConnect(const std::error_code& e);

  void writeHeader();
  void onHeaderWrite(const std::error_code& e, const std::size_t bytes);

private:
  asio::ip::tcp::socket socket_;
  char buffer_[BUFFER_SIZE];
};

Client::Client(asio::io_service& service) 
  :  socket_(service)
{

}

void Client::connect(const asio::ip::tcp::endpoint& ep) {
  socket_.async_connect(ep, std::bind(&Client::onConnect, this, std::placeholders::_1));
}

void Client::onConnect(const std::error_code& e) {
  if (!e) {
      std::cout << "Connected to the server, writing header" << std::endl; 
      writeHeader();
  } else {
      std::cout << "Connect error: " << e.message() << std::endl;
  }
}

void Client::writeHeader() {
  std::strcpy(buffer_, "Hello!");
  asio::async_write(socket_, asio::buffer(buffer_, HEADER_SIZE),
                    std::bind(&Client::onHeaderWrite, this, std::placeholders::_1, std::placeholders::_2));
}

void Client::onHeaderWrite(const std::error_code& e, const std::size_t bytes) {
  if (!e) {
      std::cout << "Header sent, size: " << bytes << std::endl;
  } else {
      std::cout << "Header write error: " << e.message() << std::endl;
  }
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
