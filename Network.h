#define ASIO_STANDALONE
#include <asio.hpp>

#define HEADER_SIZE sizeof(MessageHeader)
#define BUFFER_SIZE 256

struct MessageHeader {
  std::size_t size;
};

struct Message {
  std::uint8_t clientId;
};
