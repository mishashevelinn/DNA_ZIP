cmake_minimum_required(VERSION 3.16)
project(DNA C)

set(CMAKE_C_STANDARD 99)

add_executable(DNA main.c dna.c dna.h)