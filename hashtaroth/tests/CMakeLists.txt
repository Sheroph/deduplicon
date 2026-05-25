cmake_minimum_required(VERSION 3.14)
project(HASHTAROTH_TEST)

set(CMAKE_CXX_STANDARD 17)

# Find OpenSSL (if installed)
find_package(OpenSSL REQUIRED)

set(HASHTAROTH_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

# Define sources directory
set(HASHTAROTH_SRC_DIR "${HASHTAROTH_ROOT_DIR}/src")

# set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HDR_DIR "${HASHTAROTH_ROOT_DIR}/includes")

# Definde private headers directory
set(PRIV_HDR_DIR ${HASHTAROTH_SRC_DIR}/internal)

# Define sources
set(SOURCES ${HASHTAROTH_SRC_DIR}/hash_data.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# target_compile_options(${PROJECT_NAME} PRIVATE -DHASHTAROTH_EXPORT)

target_include_directories(${PROJECT_NAME} PRIVATE ${PRIV_HDR_DIR} 
                                           PRIVATE ${HDR_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)
