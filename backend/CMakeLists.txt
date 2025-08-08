cmake_minimum_required(VERSION 3.12)
project(backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED PATHS /usr/local/opencv4 NO_DEFAULT_PATH)
find_package(ixwebsocket REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Crow REQUIRED)
find_package(SQLiteCpp REQUIRED)
find_package(fmt REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

#
#   Camera
#

file(GLOB camera_src CONFIGURE_DEPENDS "camera/src/*.cpp" "camera/src/*.c" "shared/src/*.cpp" "shared/src/*.c")
file(GLOB camera_inc CONFIGURE_DEPENDS "camera/include" "shared/include")

add_executable(camera ${camera_src})

target_include_directories(camera PUBLIC ${camera_inc})
target_include_directories(camera PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(camera PRIVATE ${OpenCV_LIBS} ixwebsocket ZLIB::ZLIB nlohmann_json::nlohmann_json)

#
#   Server
#

file(GLOB server_src CONFIGURE_DEPENDS "server/src/*.cpp" "server/src/*.c" "shared/src/*.cpp" "shared/src/*.c")
file(GLOB server_inc CONFIGURE_DEPENDS "server/include" "shared/include")

add_executable(server ${server_src})

target_include_directories(server PUBLIC ${server_inc})
target_link_libraries(server PUBLIC Crow::Crow SQLiteCpp fmt)