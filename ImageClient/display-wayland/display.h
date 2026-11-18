#pragma once
#include <stdint.h>
#include "Image.h"


#define COLOR_BPP 4

struct raw_image {
    int width;
    int height;
    int stride;
    // uint8_t *pix[][][];
};

struct color {
    int red;
    int green;
    int blue;
    int alpha;
};

struct raw_color {
    int32_t width;
    int32_t height;
    struct color *color;
};

#ifdef __cplusplus
extern "C" {
#endif

// void display_window_image(struct raw_image *image);
// void display_window_color(struct raw_color *color);
void draw_window_image(Image &image);

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