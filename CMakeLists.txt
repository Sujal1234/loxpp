cmake_minimum_required(VERSION 3.18)
project(LoxCpp VERSION 1.0
			DESCRIPTION "Interpreter for the lox language in C++"
			LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
# C++ requirements for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC_FILES src/main.cpp src/lox.cpp src/scanner.cpp
src/token.cpp src/parser.cpp src/printer.cpp src/interpreter.cpp src/state.cpp)
add_executable(lox ${SRC_FILES})

target_include_directories(lox PUBLIC include)

if ( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
  target_compile_options( lox PRIVATE
	-Wall
	-Wextra
	-Wshadow
	-Wnon-virtual-dtor
	-Wold-style-cast
	-Woverloaded-virtual
	-Wzero-as-null-pointer-constant
	-pedantic
	-fPIE
	-fstack-protector-all
	-fno-rtti
)
endif()

