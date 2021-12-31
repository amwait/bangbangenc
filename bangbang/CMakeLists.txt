cmake_minimum_required(VERSION 3.21)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled1 main.cpp EncryptOneBlock.cpp EncryptOneBlock.h EncryptCBC.cpp EncrypyCBC.h DecryptCBC.cpp DecryptCBC.h
        DecryptOneBlock.cpp DecryptOneBlock.h common.cpp common.h
        bangbang.cpp bangbang.h
        base64new.cpp base64new.h)
