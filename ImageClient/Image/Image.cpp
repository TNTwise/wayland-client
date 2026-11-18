#include "stb_image.h"
#include "Image.h"
#include <string>
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

void Image::write_to_anon_file(int fb) const {

}