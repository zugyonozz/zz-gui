cmake_minimum_required(VERSION 3.10)
project(zz-gui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # <-- Tambahkan ini

add_executable(zz-gui
    src/main.cpp
)

target_include_directories(zz-gui
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(zz-gui
    PRIVATE
        -Wall
        -Wextra
)