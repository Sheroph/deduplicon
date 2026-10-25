cmake_minimum_required(VERSION 4.3.0)
project(BASHAZEL)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp
                               ${SRC_DIR}/commands.cpp
                               ${SRC_DIR}/command_parser.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})
