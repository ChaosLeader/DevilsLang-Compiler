cmake_minimum_required(VERSION 2.8)
project(Compiler)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

find_package(Qt5Core REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${Qt5Core_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(SOURCE_FILES main.cpp Class.cpp Class.h Parser.cpp Parser.h TokenParser.cpp Package.cpp Package.h File.cpp File.h Token.h Token.cpp)
add_executable(compiler ${SOURCE_FILES})
target_link_libraries(compiler Qt5::Core)