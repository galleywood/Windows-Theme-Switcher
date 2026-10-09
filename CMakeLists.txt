cmake_minimum_required(VERSION 4.3)
project(ThemeSwitcher)

set(CMAKE_CXX_STANDARD 20)

add_executable(ThemeSwitcher WIN32 main.cpp)

target_link_libraries(ThemeSwitcher advapi32 user32)
