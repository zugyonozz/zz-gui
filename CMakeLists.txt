cmake_minimum_required(VERSION 3.20)
project(zz-gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Windows SDK Configuration
if(WIN32)
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_SYSTEM_VERSION 10.0.26100.0)
    
    # Set Windows SDK paths
    set(WIN_SDK_ROOT "D:/dev-tools/win-sdk")
    set(WIN_SDK_VERSION "10.0.26100.0")
    
    # Include directories
    include_directories(
        "${WIN_SDK_ROOT}/Include/${WIN_SDK_VERSION}/ucrt"
        "${WIN_SDK_ROOT}/Include/${WIN_SDK_VERSION}/um"
        "${WIN_SDK_ROOT}/Include/${WIN_SDK_VERSION}/shared"
        "${WIN_SDK_ROOT}/Include/${WIN_SDK_VERSION}/winrt"
    )
    
    # Library directories
    link_directories(
        "${WIN_SDK_ROOT}/Lib/${WIN_SDK_VERSION}/ucrt/x64"
        "${WIN_SDK_ROOT}/Lib/${WIN_SDK_VERSION}/um/x64"
    )
endif()

# Your project includes
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(zz-gui ${SOURCES})

# Link Windows libraries
if(WIN32)
    target_link_libraries(zz-gui
        user32
        gdi32
        shell32
        kernel32
    )
endif()

# Compiler flags untuk Clang on Windows
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(zz-gui PRIVATE
        -Wall
        -Wextra
        -fms-extensions
        -fms-compatibility
        -Wno-microsoft-enum-value
    )
endif()