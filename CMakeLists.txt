# cmake_minimum_required(VERSION <specify CMake version here>)
project(Server)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)

add_executable(Server
        headers/bed.h
        headers/deur.h
        headers/fileHandle.h
        headers/meubel.h
        headers/schemerlamp.h
        headers/socketService.h
        bed.cpp
        deur.cpp
        fileHandle.cpp
        main.cpp
        meubel.cpp
        schemerlamp.cpp
        socketService.cpp)
