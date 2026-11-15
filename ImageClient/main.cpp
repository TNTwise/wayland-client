#include "display-wayland/display.h"
#include "extern/stb_image.h"


int main(int argc, char* argv[]) {
    int width, height, bpp;
    uint8_t* rgb_image = stbi_load(argv[0], &width, &height, &bpp, 3);
    stbi_image_free(rgb_image);
    return 0;
}