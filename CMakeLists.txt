cmake_minimum_required(VERSION 3.13) # target_compile_options in 3.13

# Name the project
project(cocles)

include_directories(include)

set(LIBCOCLES_SOURCES
	src/Application.cpp
	src/main.cpp)

# Define executable and required source files
add_executable(cocles ${LIBCOCLES_SOURCES})

# Compile with the latest C++ standard
target_compile_options(cocles PUBLIC -std=c++17)

# Enable all available warnings
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	target_compile_options(cocles PUBLIC -Weverything)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	target_compile_options(cocles PUBLIC -Wall -Wextra)
else()
	message(SEND_ERROR "Unknown compiler: " ${CMAKE_CXX_COMPILER_ID})
endif()
target_compile_options(cocles PUBLIC -pedantic)
