cmake_minimum_required(VERSION 3.10)
project(paper-play)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.c utilities.c utilities.h)

add_executable(paper-play ${SOURCE_FILES})