#include "stb_image.h"
#include "Image.h"
#include <string>
#include <syscall.h>
#include <unistd.h>
#include <sys/mman.h>
#include <array>
using namespace std;

Image::Image(const string &file_path) : file_path{file_path} {
    int width, height, channels;
    this->image_bytes = stbi_load(file_path.c_str(), &width, &height, &channels, 3);
    this->width = width;
    this->height = height;
    this->channels = channels;
    if (channels > 3) {
        this->contains_alpha = true;
    }

}
Image::Image(const Image& image) : Image{image.file_path} {}

Image& Image::operator=(const Image& other){
    return *this;
}

int Image::get_height() const {
    return this->height;
}

int Image::get_width() const {
    return this->width;
}

int Image::get_channels() const {
    return this->channels;
}

u_int8_t* Image::get_pixel_location(int x, int y) const {
    return this->image_bytes + (x + get_width() * y) * get_channels();
}

int Image::get_shared_memory() const {
    // open an anonymous file and write some zero bytes to it
    int fd = syscall(SYS_memfd_create, "buffer", 0);
    int stride = get_width() * get_channels();
    int size = stride * get_height();  // bytes
    ftruncate(fd, size);

    // map it to the memory
    unsigned char *data = static_cast<unsigned char*>(mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    // we need to make this into a function to write pixel data.
    // write to that memory.
    for (int x = 0; x < get_width(); x++) {
    for (int y = 0; y < get_height(); y++) {

        struct pixel {
            // little-endian ARGB
            unsigned char blue;
            unsigned char green;
            unsigned char red;
            unsigned char alpha;
        } *px = (struct pixel *) (data + y * stride + x * 4);
        
        // this links to the start of image bytes, and uses ptr arithmatic to get the offset to where in the list the current pixel is.
        u_int8_t* pxl_offset = get_pixel_location(x, y);

        px->alpha = 255;
        px->red = pxl_offset[0];
        px->green = pxl_offset[1];
        px->blue = pxl_offset[2];
        }
    }

    return fd;
}

Image::~Image() {
    stbi_image_free(this->image_bytes);
}

void Image::validate_x_y(int x, int y) const {
    assert(x < width && x >= 0);
    assert(y < height && y >= 0);
}

int Image::get_red_value(int x, int y) const {
    validate_x_y(x, y);
    return get_pixel_location(x, y)[0];
}

int Image::get_green_value(int x, int y) const {
    validate_x_y(x, y);
    return get_pixel_location(x, y)[1];
}

int Image::get_blue_value(int x, int y) const {
   validate_x_y(x, y);
    return get_pixel_location(x, y)[2]; 
}

int Image::get_alpha_value(int x, int y) const {
    assert(contains_alpha == true);
    validate_x_y(x, y);
    return get_pixel_location(x, y)[3];
}



void Image::modify_pixel(int x, int y, int r, int g, int b) {
    validate_x_y(x, y);
    assert(r >= 0 && r <= 255);
    assert(g >= 0 && g <= 255);
    assert(b >= 0 && b <= 255);
    u_int8_t* pxl_offset = get_pixel_location(x, y);
    pxl_offset[0] = r;
    pxl_offset[1] = g;
    pxl_offset[2] = b;
}