cmake_minimum_required(VERSION 4.3.0)
project(HASHTAROTH)

set(CMAKE_CXX_STANDARD 17)

# Find OpenSSL (if installed)
find_package(OpenSSL REQUIRED)

# Define sources directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Define sources
set(SOURCES ${SRC_DIR}/hashtaroth.cpp
            ${SRC_DIR}/hash_response.cpp
            ${SRC_DIR}/hash_job.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)
