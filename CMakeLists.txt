cmake_minimum_required(VERSION 3.20)
project(proyecto-infoII)

set(CMAKE_CXX_STANDARD 14)
include_directories("D:\\mingw64\\include")

add_executable(proyecto main.cpp
        .//SourceFiles//Game.cpp
        .//SourceFiles//Map.cpp
        .//SourceFiles//Player.cpp
        .//SourceFiles//Bullet.cpp
        .//SourceFiles//Enemies.cpp
        )

target_link_libraries(proyecto sfml-graphics sfml-audio sfml-system sfml-window)






