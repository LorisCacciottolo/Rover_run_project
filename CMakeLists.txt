cmake_minimum_required(VERSION 3.27)
project(Rover_run_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(MARC-master)

add_executable(Rover_run_project
        MARC-master/loc.c
        MARC-master/loc.h
        MARC-master/main.c
        MARC-master/map.c
        MARC-master/map.h
        MARC-master/moves.c
        MARC-master/moves.h
        MARC-master/queue.c
        MARC-master/queue.h
        MARC-master/stack.c
        MARC-master/stack.h
        README.md)
