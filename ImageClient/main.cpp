#include <iostream>
#include "display-wayland/display.h"
#define STB_IMAGE_IMPLEMENTATION
#include "extern/stb_image.h"

using namespace std;

int main(int argc, char* argv[]) {
    int width, height, bpp;
    
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
    return 0;
}