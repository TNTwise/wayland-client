#include "stb_image.h"
#include "Image.h"
#include <string>
#include <array>
using namespace std;

Image::Image(const string &file_path) : file_path{file_path} {
    int width, height, channels;
    u_int8_t *img = stbi_load(file_path.c_str(), &width, &height, &channels, 3);

    struct raw_image raw_image = {
        .width = width,
        .height = height,
        .bbp = channels,
        .pixels = new pixel[width*height] // yes this will cause a memory leak
    };

    if (img == NULL) {
        fprintf(stderr, "Error loading image.\n");
    } else {
        printf("Loaded image.\n");
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < width; j++) {
                u_int8_t* pixel_offset = img + (i + width * j) * channels;
                u_int8_t r = pixel_offset[0];
                u_int8_t g = pixel_offset[1];
                u_int8_t b = pixel_offset[2];
                u_int8_t a = channels >= 4 ? pixel_offset[3] : 0xff;

            }
        }
    }

    

}

struct raw_image Image::get_image() const {
    return *(this->raw_image);
}