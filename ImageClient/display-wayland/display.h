#include <stdint.h>

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
void display_window_color(struct raw_color *color);
#ifdef __cplusplus
}
#endif