cmake_minimum_required(VERSION 4.3.0)
project(BEELZEBASE)

set(CMAKE_CXX_STANDARD 17)

# Define sources directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SQLITE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite)

# Define sources
set(SOURCES ${SRC_DIR}/beelzebase.cpp
            ${SRC_DIR}/sqlite/sqlite_api.cpp
            ${SRC_DIR}/sqlite/sqlite_bind_impl.cpp
            ${SRC_DIR}/records/monitored_fs_record.cpp
            ${SQLITE_DIR}/sqlite3.c)


add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${SQLITE_DIR}
)
