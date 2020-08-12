cmake_minimum_required(VERSION 3.10)

# project name / version
project(dev VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

# pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# headers
include_directories(include)

# source (global)
file(GLOB SOURCES "src/*.cpp")

# executable
add_executable(${PROJECT_NAME} ${SOURCES})

# libraries
target_link_libraries(${PROJECT_NAME} Threads::Threads)
