cmake_minimum_required(VERSION 3.10)
project(kai_shell C)

set(CMAKE_C_STANDARD 11)

# Add executable and specify sources
add_executable(kai_shell
        main.c
        kai_shell.h
        kai_shell.c
)

# Set compiler flags for both GCC and Clang
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(kai_shell PRIVATE -Wall -Wextra -pedantic)
endif()