cmake_minimum_required(VERSION 4.1)
project(moon_landing C)

set(CMAKE_C_STANDARD 11)

add_executable(moon_landing
        main.c)
target_link_libraries(moon_landing m)
