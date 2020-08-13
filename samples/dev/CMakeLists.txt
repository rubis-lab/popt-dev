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

# headers
include_directories(include)
include_directories(/usr/local/include)

# source (global)
file(GLOB SOURCES "src/*.cpp")

# executable
add_executable(${PROJECT_NAME} ${SOURCES})

# libraries
file(GLOB LIBRARIES_OSX "/usr/local/lib/librts*.dylib")
file(GLOB LIBRARIES "/usr/local/lib/librts*.so")
target_link_libraries(${PROJECT_NAME} ${LIBRARIES} ${LIBRARIES_OSX})
