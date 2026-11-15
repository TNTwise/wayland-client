#include <cstdint>

#ifndef DISPLAY
#define DISPLAY


#ifdef  __cplusplus
extern "C" {

struct raw_image {
    int width;
    int height;
    int stride;
    uint8_t* pix;
};

void display_window_image(
    raw_image raw_image
);


#endif
#ifdef  __cplusplus
}
#endif

#endif