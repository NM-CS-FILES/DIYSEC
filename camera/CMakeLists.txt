cmake_minimum_required(VERSION 3.12)
project(camera)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB camera_src CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")
file(GLOB camera_inc CONFIGURE_DEPENDS "include/*.hpp" "include/*.h")

add_executable(camera ${camera_src})
target_include_directories(camera PUBLIC ${camera_inc})

find_package(OpenCV REQUIRED)
find_package(ixwebsocket REQUIRED)

target_include_directories(camera PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(camera PRIVATE ${OpenCV_LIBS} ixwebsocket ZLIB::ZLIB)

# target_link_libraries(camera ixwebsocket::ixwebsocket)

# include_directories(/usr/local/include)
# link_directories(/usr/local/lib)


