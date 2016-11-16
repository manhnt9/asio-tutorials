#!/bin/bash
g++ -o server Server.cpp -I./asio/include -std=c++11 -pthread
g++ -o client Client.cpp -I./asio/include -std=c++11 -pthread
