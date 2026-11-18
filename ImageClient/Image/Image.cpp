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

}

int Image::get_height() const {
    return this->height;
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

        // yellow
        px->alpha = 255;
        px->red = raw_color->color->red;
        px->green = raw_color->color->green;
        px->blue = raw_color->color->blue;
        }
    }

    return fd;
}

Image::~Image() {
    stbi_image_free(this->image_bytes);
}