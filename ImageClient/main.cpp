#include <iostream>
#include "Image/Image.h"
#include "display-wayland/display.h"
#include "Image/filter.h"
#define STB_IMAGE_IMPLEMENTATION

using namespace std;

int main(int argc, char* argv[]) {
    Image image = Image(std::string("website.jpg"));
    
    // cout << image.get_height() << endl;
    // draw_color();
    // int fd = image.get_shared_memory();
    
    display_window_buffer(
        image.get_width(),
        image.get_height(),
        image.get_channels(),
        image.get_shared_memory()
    );

    return 0;

}