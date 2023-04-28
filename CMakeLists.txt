cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 11)

project(${PROJECT_NAME} C)
set(SOURCE_FILES main.c)

# use this to find the brew package.
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})