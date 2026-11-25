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
        
    }
    BaseImage(const BaseImage& image) : BaseImage{image.file_path} {}
    BaseImage& operator=(const BaseImage& image) {
        return *this;
    }
    virtual ~BaseImage() = default;

    virtual int get_height() const = 0;

    virtual int get_width() const = 0;
    virtual int get_channels() const = 0;
    virtual void modify_pixel(int x, int y, int r, int g, int b, int a) = 0;
    virtual BaseImage& filter() = 0;
};