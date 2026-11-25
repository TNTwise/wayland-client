#include "Image.h"
#include "filter.h"

Image& RedFilter(Image& image) {
    for (int i = 0; i < image.get_width(); i++) {
        for (int j = 0; j < image.get_height(); j++) {
            image.modify_pixel(i, j, image.get_red_value(i, j), 0, 0);
        }
    }
    return image;
}