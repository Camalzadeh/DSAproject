cmake_minimum_required(VERSION 3.29)
project(DSAproject C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(DSAproject
        main.c
        dsaproject.c
        )
