cmake_minimum_required(VERSION 3.15)
project(MTP)

set(CMAKE_CXX_STANDARD 14)

add_executable(MTP main.cpp CipherString.cpp CipherString.hpp mtp.cpp mtp.hpp MtpAnalyzer.cpp MtpAnalyzer.hpp)