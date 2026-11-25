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

Image& GreenFilter(Image& image) {
    for (int i = 0; i < image.get_width(); i++) {
        for (int j = 0; j < image.get_height(); j++) {
            image.modify_pixel(i, j, 0, image.get_green_value(i, j), 0);
        }
    }
    return image;
}

Image& BlueFilter(Image& image) {
    for (int i = 0; i < image.get_width(); i++) {
        for (int j = 0; j < image.get_height(); j++) {
            image.modify_pixel(i, j, 0, 0, image.get_blue_value(i, j));
        }
    }
    return image;
}

Image& BlurFilter(Image& image) {
    int stride = 1;

    for (int i = stride; i < image.get_width() - stride; i++) {
        for (int j = stride; j < image.get_height() - stride; j++) {
            
            for (int channels = 0; channels < image.get_channels(); channels++) {
                int average = 0;
                for (int x = i-1; x <= i+1; x++) {
                    for (int y = j-1; y <= j+1; y++) {
                        average += image.get_pixel_value(x, y, channels);
                    }
                }
                average = average / 9;
                
                for (int x = i-1; x < i+1; x++) {
                    for (int y = j-1; y < j+1; y++) {
                        image.modify_pixel(x,y,channels,average);
                    }
                }
            }
        }
    }
    return image;
}
