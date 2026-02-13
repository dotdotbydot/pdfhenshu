cmake_minimum_required(VERSION 3.16)
project(pdfhenshu C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(PDFHENSHU_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(PDFHENSHU_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(PDFHENSHU_SOURCES
    "${PDFHENSHU_SRC_DIR}/main.c"
    "${PDFHENSHU_SRC_DIR}/config.c"
)

foreach(src_file IN LISTS PDFHENSHU_SOURCES)
    if(NOT EXISTS "${src_file}")
        message(FATAL_ERROR
            "Missing source file: ${src_file}\n"
            "Open the repository root folder in VSCode/Visual Studio.\n"
            "Expected layout:\n"
            "  CMakeLists.txt\n"
            "  src/main.c\n"
            "  src/config.c\n"
            "  include/config.h")
    endif()
endforeach()

add_executable(pdfhenshu ${PDFHENSHU_SOURCES})
target_include_directories(pdfhenshu PRIVATE "${PDFHENSHU_INCLUDE_DIR}")

if(MSVC)
    target_compile_definitions(pdfhenshu PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(pdfhenshu PRIVATE /W4)
else()
    target_compile_options(pdfhenshu PRIVATE -Wall -Wextra -Wpedantic)
endif()
