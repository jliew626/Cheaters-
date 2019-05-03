cmake_minimum_required(VERSION 3.13)
project(plagiarismCatcher)

set(CMAKE_CXX_STANDARD 11)

add_executable(plagiarismCatcher main.cpp hashTab.h hashTab.cpp)