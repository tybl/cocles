# Hints: http://www.brianlheim.com/2018/04/09/cmake-cheat-sheet.html
project(cocles)
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

set(EXEC_NAME cocles)
set(LIB_NAME ledger)
set(LIB_SOURCES
	src/ledger/parse/transaction.cpp
	src/ledger/util/Money.cpp
	src/ledger/util/stringify_arguments.cpp)
set(TEST_NAME libledgertest)
set(TEST_SOURCES
	test/ledger/parse/transaction.cpp)

include_directories(include src)
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

add_executable(${EXEC_NAME} src/main.cpp)
target_link_libraries(${EXEC_NAME} ${LIB_NAME})

enable_testing()

add_executable(${TEST_NAME} test/main.cpp ${TEST_SOURCES})
target_link_libraries(${TEST_NAME} ${LIB_NAME})
add_test(${TEST_NAME} ${TEST_NAME})

# Enable all available warnings
if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
	target_compile_options(${LIB_NAME} PUBLIC -Weverything -Wno-c++98-compat)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	target_compile_options(${LIB_NAME} PUBLIC -Wall -Wextra)
else()
	message(SEND_ERROR "Unknown compiler: " ${CMAKE_CXX_COMPILER_ID})
endif()
target_compile_options(${LIB_NAME} PUBLIC -pedantic)

