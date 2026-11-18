cmake_minimum_required(VERSION 3.16)
project(ImageViewer LANGUAGES C CXX)

# main.cpp uses designated initializers (.red = ...), which are C++20.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(display-wayland)
add_subdirectory(Image)


add_executable(ImageViewer
    main.cpp
)

# Lets sources include "stb_image.h" / "Image.h" directly.
target_include_directories(ImageViewer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Image
)

target_include_directories(ImageViewer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Image"
)


target_link_libraries(ImageViewer PRIVATE display-wayland Image)