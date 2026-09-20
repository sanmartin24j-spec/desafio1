cmake_minimum_required(VERSION 3.16)

project(desafio1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(desafio1
    main.cpp
    tablero.h
    tablero.cpp
)