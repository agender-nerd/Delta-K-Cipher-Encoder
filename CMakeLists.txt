cmake_minimum_required(VERSION 3.10)

project(Delta-K_Cipher VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(delta-k
    src/main.cpp
    src/Delta_K.cpp
)