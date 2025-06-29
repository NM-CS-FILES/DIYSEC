cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB server_src CONFIGURE_DEPENDS "../src/*.cpp" "../src/*.c")
file(GLOB server_inc CONFIGURE_DEPENDS "../include/*.hpp" "../include/*.h")

add_executable(server ${server_src})
target_include_directories(server PUBLIC ${server_inc})

find_package(Crow REQUIRED)
target_link_libraries(server PUBLIC Crow::Crow)

find_package(SQLiteCpp REQUIRED)
target_link_libraries(server PUBLIC SQLiteCpp)

find_package(fmt REQUIRED)
target_link_libraries(server PUBLIC fmt)
