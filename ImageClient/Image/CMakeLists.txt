add_library(Image
    Image.cpp
    Color.cpp
    stb_image.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED IMPORTED_TARGET wayland-client)

target_include_directories(Image
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Image PUBLIC PkgConfig::WAYLAND_CLIENT)

target_compile_features(Image PUBLIC cxx_std_17)