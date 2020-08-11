cmake_minimum_required(VERSION 3.10)

# project name / version
project(EG1 VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

# no test for nlohmann
set(JSON_BuildTests OFF CACHE INTERNAL "")
# no install
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

# pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# headers
include_directories(include)

# json
# find_package(nlohmann_json 2.1.1 REQUIRED)


# source (manual)
# set(SOURCES src/main.cpp src/sched_deadline.cpp)
# source (global)
file(GLOB SOURCES "src/*.cpp")

# executable
add_executable(${PROJECT_NAME} ${SOURCES})

# libraries
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
