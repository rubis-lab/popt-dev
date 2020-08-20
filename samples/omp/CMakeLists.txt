cmake_minimum_required(VERSION 3.10)

# project name / version
project(omp VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

# packages
if(APPLE)
    find_package(spdlog REQUIRED)
endif()

# headers
include_directories(include)
include_directories(/usr/local/include)
include_directories(/usr/local/include/rts)
if(UNIX AND NOT APPLE)
    include_directories(/usr/include/spdlog)
endif()

# source (global)
file(GLOB SOURCES "src/*.cpp")

# executable
add_executable(${PROJECT_NAME} ${SOURCES})

# libraries
if(APPLE)
    file(GLOB LIBRARIES_OSX "/usr/local/lib/librts*.dylib")
    target_link_libraries(${PROJECT_NAME} ${LIBRARIES_OSX})
    target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
    file(GLOB LIB_FMT_OSX "/usr/local/lib/libfmt.dylib")
    target_link_libraries(${PROJECT_NAME} ${LIB_FMT_OSX})
endif()
if(UNIX AND NOT APPLE)
    file(GLOB LIBRARIES "/usr/local/lib/librts*.so")
    target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
endif()




