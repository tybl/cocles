cmake_minimum_required(VERSION 3.13) # target_compile_options in 3.13

# Name the project
project(cocles)

enable_testing()

include_directories(
	include
	src)

set(LIBCOCLES_SOURCES
	src/ledger/parse/transaction.cpp
	src/ledger/util/Money.cpp
	src/ledger/util/stringify_arguments.cpp)

set(LIBCOCLES_TEST_SOURCES
	${LIBCOCLES_SOURCES}
	test/ledger/parse/transaction.cpp)

# Define executable and required source files
add_executable(cocles
	src/main.cpp
	${LIBCOCLES_SOURCES})

add_executable(UnitTests
	test/main.cpp
	${LIBCOCLES_TEST_SOURCES})

add_test(UnitTests UnitTests)

# Compile with the latest C++ standard
target_compile_options(cocles PUBLIC -std=c++17)

# Enable all available warnings
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	target_compile_options(cocles PUBLIC -Weverything -Wno-c++98-compat)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
	target_compile_options(cocles PUBLIC -Weverything -Wno-c++98-compat)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	target_compile_options(cocles PUBLIC -Wall -Wextra)
else()
	message(SEND_ERROR "Unknown compiler: " ${CMAKE_CXX_COMPILER_ID})
endif()
target_compile_options(cocles PUBLIC -pedantic)

# Compile with the latest C++ standard
target_compile_options(UnitTests PUBLIC -std=c++17)

# Enable all available warnings
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	target_compile_options(UnitTests PUBLIC -Weverything -Wno-c++98-compat)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
	target_compile_options(UnitTests PUBLIC -Weverything -Wno-c++98-compat)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	target_compile_options(UnitTests PUBLIC -Wall -Wextra)
else()
	message(SEND_ERROR "Unknown compiler: " ${CMAKE_CXX_COMPILER_ID})
endif()
target_compile_options(UnitTests PUBLIC -pedantic)
