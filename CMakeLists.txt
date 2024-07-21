cmake_minimum_required(VERSION 3.26)
project(PONG)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR C:/Users/Angel/.vcpkg-clion/vcpkg/installed/x64-windows/share/sfml)

add_executable(PONG main.cpp)

find_package(SFML 2.5 COMPONENTS graphics system window CONFIG REQUIRED)

target_link_libraries(PONG sfml-graphics sfml-system sfml-window)