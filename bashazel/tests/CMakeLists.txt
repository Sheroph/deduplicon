cmake_minimum_required(VERSION 4.3.0)
project(BASHAZEL_TEST)

set(CMAKE_CXX_STANDARD 17)

set(BASHAZEL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(BASHAZEL_SRC "${BASHAZEL_ROOT_DIR}/src")
set(BASHAZEL_INC "${BASHAZEL_ROOT_DIR}/include")

set(SOURCES command_parser_tests.cpp
            ${BASHAZEL_SRC}/command_parser.cpp
            ${BASHAZEL_SRC}/commands.cpp)

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

target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PRIVATE ${BASHAZEL_INC})

gtest_discover_tests(${PROJECT_NAME})
