cmake_minimum_required(VERSION 3.10)

# project name / version
project(rts VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# no test for nlohmann
set(JSON_BuildTests OFF CACHE INTERNAL "")
# no install
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(lib/nlohmann_json)

# pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# headers
include_directories(include)

# source (manual)
# set(SOURCES src/main.cpp src/sched_deadline.cpp)
# source (global)
file(GLOB SOURCES "src/*.cpp")

# executable
# add_executable(${PROJECT_NAME} ${SOURCES})

# library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/thr.hpp
    PUBLIC_HEADER include/task.hpp
    PUBLIC_HEADER include/task_set.hpp
    PUBLIC_HEADER include/pt.hpp
    PUBLIC_HEADER include/pts.hpp)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
target_include_directories(${PROJECT_NAME} PRIVATE .)

# libraries
# target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

# Shared library
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rts)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
