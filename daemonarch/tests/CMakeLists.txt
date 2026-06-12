cmake_minimum_required(VERSION 4.3.0)
project(DAEMONARCH_TEST)

set(CMAKE_CXX_STANDARD 17)

set(DAEMONARCH_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_subdirectory(${DAEMONARCH_ROOT_DIR} ${CMAKE_CURRENT_BINARY_DIR}/deps/daemonarch)

set(MOCK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mocks)
set(TOOLS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools)

set(SOURCES main.cpp
            ${MOCK_DIR}/daemonarch_listener_mock.cpp
            ${TOOLS_DIR}/file_modifier.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${MOCK_DIR} ${TOOLS_DIR})

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

target_link_libraries(${PROJECT_NAME} DAEMONARCH GTest::gtest_main)

gtest_discover_tests(DAEMONARCH_TEST)
