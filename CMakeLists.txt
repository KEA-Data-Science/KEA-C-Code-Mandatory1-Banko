cmake_minimum_required(VERSION 3.17)
project(Banko1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Banko1 main.c bankoboard.h miscmath.h bankoboard.c)