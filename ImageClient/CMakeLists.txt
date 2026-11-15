cmake_minimum_required(VERSION 3.16)
project(ImageViewer LANGUAGES C CXX)



add_subdirectory(display-wayland)

add_executable(ImageViewer
    main.cpp)

target_include_directories(ImageViewer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/extern"
)

target_link_libraries(ImageViewer PRIVATE display-wayland)
