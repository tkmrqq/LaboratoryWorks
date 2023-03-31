cmake_minimum_required(VERSION 3.24)
project(Lab2_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Compressor main.c functions.c library.h)
add_executable(Decompress decompress.c)
