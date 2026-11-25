cmake_minimum_required(VERSION 3.16)
project(ImageViewer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT MSVC)
    set(SANITIZER_FLAGS -fsanitize=address,undefined -fno-omit-frame-pointer)
    add_compile_options(${SANITIZER_FLAGS})
    add_link_options(${SANITIZER_FLAGS})
endif()

add_subdirectory(display-wayland)
add_subdirectory(Image)

add_executable(ImageViewer
    main.cpp
)

target_include_directories(ImageViewer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Image"
)

target_link_libraries(ImageViewer PRIVATE display-wayland Image)