#pragma once
#include <string>
#include <array>



class Image {
private:
    const std::string& file_path;
    u_int8_t* image_bytes;    
    int width;
    int height;
    int channels;
    // int assign_shared_memory();
public:
    explicit Image(const std::string &file_path);
    Image(const Image& image);
    Image& operator=(const Image& image);
    ~Image();

    int get_shared_memory() const; //instead of passing it through to display.cpp, create an image in main and get fd from image itself.

    int get_height() const;

    int get_width() const;

    int get_channels() const;

    // u_int8_t get_image_bytes();

    // struct pixel get_pixel_at(u_int8_t x, u_int8_t, y);

};