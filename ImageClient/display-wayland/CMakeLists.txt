add_library(display-wayland
    display.c
    xdg-shell-protocol.c
)

target_include_directories(display-wayland
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(display-wayland PUBLIC cxx_std_17)