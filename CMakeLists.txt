cmake_minimum_required(VERSION 3.16)

project(VierGewinnt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(VierGewinnt
        src/main.cpp
        src/Board.cpp
        src/Player.cpp
        src/Game.cpp
)
