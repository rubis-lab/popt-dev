cmake_minimum_required(VERSION 3.10)

# project name / version
project(rts VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

# no test for nlohmann
set(JSON_BuildTests OFF CACHE INTERNAL "")
# no install
#set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(lib/nlohmann_json)

# packages
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if(APPLE)
    find_package(spdlog REQUIRED)
endif()


# headers
include_directories(include)
include_directories(lib/nlohmann_json/include)
if(UNIX AND NOT APPLE)
    include_directories(/usr/include/spdlog)
endif()
# include_directories(/usr/include/fmt)

# source (manual)
# set(SOURCES src/main.cpp src/sched_deadline.cpp)
# source (global)
file(GLOB SOURCES
    "src/core/*.cpp"
    "src/gen/*.cpp"
    "src/op/*.cpp"
    "src/sched/*.cpp")
# osx(brew) headers
# include_directories(/usr/local/Cellar)

# executable
# add_executable(${PROJECT_NAME} ${SOURCES})

# library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "include/core/task.hpp;\
include/core/task_set.hpp;\
include/core/thread.hpp;\
include/core/pt.hpp;\
include/core/pts.hpp;\
include/core/dag.hpp;\
include/gen/gen.hpp;\
include/gen/egen.hpp;\
include/gen/unifast.hpp;\
include/op/tsutil.hpp;\
include/op/exp.hpp;\
include/op/stat.hpp;\
include/sched/gfb.hpp;\
include/sched/bcl.hpp;\
include/sched/cho.hpp")

# target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libspdlog.so)
# target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libfmt.a)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
target_include_directories(${PROJECT_NAME} PRIVATE .)

# libraries
# target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
endif()
# target_link_libraries(${PROJECT_NAME} fmt::fmt-header-only)

if(APPLE)
    file(GLOB LIB_FMT_OSX "/usr/local/lib/libfmt.dylib")
    target_link_libraries(${PROJECT_NAME} ${LIB_FMT_OSX})
endif()

# Shared library
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY "include/" # source directory
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rts # target directory
    FILES_MATCHING # install only matched files
    PATTERN "*.hpp") # select header files
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
