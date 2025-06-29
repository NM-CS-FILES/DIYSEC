cmake_minimum_required(VERSION 3.12)
project(camera)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB camera_src CONFIGURE_DEPENDS "../src/*.cpp" "../src/*.c")
file(GLOB camera_inc CONFIGURE_DEPENDS "../include/*.hpp" "../include/*.h")

add_executable(camera ${camera_src})
target_include_directories(camera PUBLIC ${camera_inc})

find_package(OpenCV REQUIRED)
target_link_libraries(camera PUBLIC OpenCV)

find_package(gstreamer REQUIRED)
