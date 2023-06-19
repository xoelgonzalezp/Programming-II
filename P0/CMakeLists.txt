cmake_minimum_required(VERSION 3.24)
project(Rational C)

set(CMAKE_C_STANDARD 99)

add_executable(Rational_struct main.c rational_struct.c rational_struct.h )
add_executable(Rational_pointer main.c rational_pointer.c rational_pointer.h )