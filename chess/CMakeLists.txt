cmake_minimum_required(VERSION 3.14)
project(chess_try2)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess_try2 main.cpp figure.h figure.cpp board.h board.cpp chess.h chess.cpp)