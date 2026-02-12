cmake_minimum_required(VERSION 3.16)
project(pdfhenshu C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(pdfhenshu
    src/main.c
    src/config.c
)

target_include_directories(pdfhenshu PRIVATE include)

if(MSVC)
    target_compile_definitions(pdfhenshu PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(MSVC)
    target_compile_options(pdfhenshu PRIVATE /W4)
else()
    target_compile_options(pdfhenshu PRIVATE -Wall -Wextra -Wpedantic)
endif()
