#include <iostream>
#include "display-wayland/display.h"
#define STB_IMAGE_IMPLEMENTATION
#include "extern/stb_image.h"

using namespace std;

int main(int argc, char* argv[]) {
    int width, height, bpp;
    /*
    uint8_t* rgb_image = stbi_load("website.jpg", &width, &height, &bpp, 3);
    struct raw_image raw_image = {
        .width = width,
        .height = height,
        .stride = bpp,
        .pix = rgb_image
        
    };
    cout << width << endl;
    cout << height << endl;
    cout << bpp << endl;

    stbi_image_free(rgb_image);
    
    display_window_image(raw_image);
    */

    width = 200;
    height = 300;
    struct color color = {
        .red = 255,
        .green = 0,
        .blue = 0,
        .alpha = 0
    };
    struct raw_color raw_color = {
        .width = width,
        .height = height,
        .color = &color
        
    };

    display_window_color(&raw_color);
    return 0;
}