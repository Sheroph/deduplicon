cmake_minimum_required(VERSION 3.14)
project(HASHTAROTH_TEST)

set(CMAKE_CXX_STANDARD 17)

set(HASHTAROTH_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_subdirectory(${HASHTAROTH_ROOT_DIR} ${CMAKE_CURRENT_BINARY_DIR}/deps/hashtaroth)

set(SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

target_link_libraries(${PROJECT_NAME} HASHTAROTH GTest::gtest_main)

gtest_discover_tests(HASHTAROTH_TEST)
