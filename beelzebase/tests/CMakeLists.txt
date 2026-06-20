cmake_minimum_required(VERSION 4.3.0)
project(BEELZEBASE_TEST)

set(CMAKE_CXX_STANDARD 17)

set(BEELZEBASE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_subdirectory(${BEELZEBASE_ROOT_DIR} ${CMAKE_CURRENT_BINARY_DIR}/deps/beelzebase)

set(SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

target_link_libraries(${PROJECT_NAME} BEELZEBASE GTest::gtest_main)

gtest_discover_tests(BEELZEBASE_TEST)
