#include "stb_image.h"
#include "Image.h"
#include <string>
#include <unistd.h>
#include <sys/mman.h>
using namespace std;

Image::Image(const string &file_path) : BaseImage(file_path) {

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
        u_int8_t* pxl_offset = this->image_bytes + (x + get_width() * y) * get_channels();

        // yellow
        px->alpha = 255;
        px->red = pxl_offset[0];
        px->green = pxl_offset[1];
        px->blue = pxl_offset[2];
        }
    }

    return fd;
}