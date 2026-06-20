cmake_minimum_required(VERSION 4.3.0)
project(BEELZEBASE)

set(CMAKE_CXX_STANDARD 17)

# Define sources directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SQLITE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite)

# Define sources
set(SOURCES ${SRC_DIR}/beelzebase.cpp
            ${SRC_DIR}/sqlite_api.cpp
            ${SQLITE_DIR}/sqlite3.c)


add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${SQLITE_DIR}
)
