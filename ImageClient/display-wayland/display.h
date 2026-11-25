#pragma once
#include <stdint.h>



#ifdef __cplusplus
extern "C" {
#endif

#ifndef DISPLAY_WINDOW_BUFFER
#define DISPLAY_WINDOW_BUFFEr
void display_window_buffer(
    int32_t width,
    int32_t height,
    int bpp,
    int fd
);
#endif

#ifdef __cplusplus
}
#endif