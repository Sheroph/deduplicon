cmake_minimum_required(VERSION 4.3.0)
project(DAEMONARCH)

set(CMAKE_CXX_STANDARD 17)

# Define sources directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Define sources
set(SOURCES ${SRC_DIR}/daemonarch.cpp
            ${SRC_DIR}/event_translate_tools.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

