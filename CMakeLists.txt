cmake_minimum_required(VERSION 3.10)

project(Delta-K_Cipher VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(delta-k
    src/main.cpp
    src/delta-k.cpp
)