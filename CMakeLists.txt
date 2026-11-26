cmake_minimum_required(VERSION 3.16)
project(VierGewinnt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(VierGewinnt
    src/main.cpp
    src/Board.cpp
    src/Player.cpp
    src/Game.cpp
    src/GameRepository.cpp
    src/Replay.cpp
    src/ComputerPlayer.cpp
    src/Statistics.cpp
)

enable_testing()

add_executable(VierGewinntTests
    tests/tests.cpp
    src/Board.cpp
    src/ComputerPlayer.cpp
    src/GameRepository.cpp
    src/Statistics.cpp
)

target_include_directories(VierGewinntTests PRIVATE src)
add_test(NAME VierGewinntTests COMMAND VierGewinntTests)
