cmake_minimum_required(VERSION 3.12)
project(WinSocket)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32 wsock32)
add_executable(WinSocket server.cpp main.cpp)