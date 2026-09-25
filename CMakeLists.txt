cmake_minimum_required(VERSION 3.20)

project(gbemu
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(gbemu
    src/main.cpp
    src/cpu.cpp
    src/opcodes.cpp
)

target_include_directories(gbemu
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if (MSVC)
    target_compile_options(gbemu PRIVATE /W4)
else()
    target_compile_options(gbemu PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()