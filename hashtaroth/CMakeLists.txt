cmake_minimum_required(VERSION 3.14)
project(HASHTAROTH)

set(CMAKE_CXX_STANDARD 17)

# Find OpenSSL (if installed)
find_package(OpenSSL REQUIRED)

# Define sources directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Definde private headers directory
set(PRIV_HDR_DIR ${SRC_DIR}/internal)

# Define sources
set(SOURCES
    ${SRC_DIR}/hash_extractor.cpp
    ${SRC_DIR}/hash_data.cpp
)

add_library(HASHTAROTH SHARED ${SOURCES})

target_include_directories(HASHTAROTH
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes
    PRIVATE ${PRIV_HDR_DIR}
)

# target_link_libraries(HASHTAROTH PRIVATE OpenSSL::SSL)
target_link_libraries(HASHTAROTH PRIVATE OpenSSL::Crypto)
