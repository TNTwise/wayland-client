find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED IMPORTED_TARGET wayland-client)

add_library(display-wayland STATIC
    display.c
    xdg-shell-protocol.c
)

# Anyone linking this library can #include "display.h".
target_include_directories(display-wayland PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(display-wayland PUBLIC PkgConfig::WAYLAND_CLIENT)
