add_library(display-wayland
    display.c
    xdg-shell-protocol.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED IMPORTED_TARGET wayland-client)

target_include_directories(display-wayland
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(display-wayland PUBLIC PkgConfig::WAYLAND_CLIENT)

target_compile_features(display-wayland PUBLIC cxx_std_17)