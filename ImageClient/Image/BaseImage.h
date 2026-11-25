#include "stb_image.h"
#include <string>
#include <syscall.h>
#include <unistd.h>
#include <sys/mman.h>
#include <array>
#pragma once
using namespace std;

class BaseImage {
private:
    const std::string& file_path;
    int width;
    int height;
    int channels;
protected:
    u_int8_t* image_bytes; // this needs to be modifiable
public:
    explicit BaseImage(const std::string &file_path) : file_path{file_path} {
        int width, height, channels;
        this->image_bytes = stbi_load(file_path.c_str(), &width, &height, &channels, 3);
        this->width = width;
        this->height = height;
        this->channels = channels;
    }
    BaseImage(const BaseImage& image) : BaseImage{image.file_path} {}
    BaseImage& operator=(const BaseImage& image) {
        return *this;
    }
    ~BaseImage() {
        stbi_image_free(this->image_bytes);
    }

    int get_height() const {
        return this->height;
    }

    int get_width() const {
        return this->width;
    }

    int get_channels() const {
        return this->channels;
    }

    BaseImage& filter(BaseImage& image);
};