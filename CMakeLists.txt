cmake_minimum_required(VERSION 3.20)
project(Bank)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bank main.cpp bank.cpp bankAdmin.cpp)
