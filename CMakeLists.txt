cmake_minimum_required(VERSION 4.3.0)
project(DEDUPLICON)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS ON)

# Make sure to don't forget deamons (they are a bit susceptible)
add_subdirectory(hashtaroth)
# add_subdirectory(beelzebase)
add_subdirectory(daemonarch)

# add_subdirectory(main)
