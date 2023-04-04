cmake_minimum_required(VERSION 3.23)
project(LaboratoryWorks C)

set(CMAKE_C_STANDARD 99)

add_executable(LaboratoryWorks src/Lab1/main.c src/Lab1/functions.c src/Lab1/library.h)
add_executable(LaboratoryWorks src/Lab2_2/main.c src/Lab2_2/functions.c src/Lab2_2/library.h src/Lab2_2/decompress.c)
