cmake_minimum_required(VERSION 4.3.0)
project(DEDUPLICON)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS ON)

# Make sure to don't forget daemons (they are a bit susceptible)
add_subdirectory(hashtaroth)
add_subdirectory(beelzebase)
add_subdirectory(daemonarch)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp
                               ${SRC_DIR}/deduplicon_listener.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE HASHTAROTH BEELZEBASE DAEMONARCH)
target_include_directories(${PROJECT_NAME} PRIVATE HASHTAROTH BEELZEBASE DAEMONARCH PUBLIC ${INC_DIR})
