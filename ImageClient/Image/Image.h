#pragma once
#include <string>
#include <array>
#include <assert.h>



class Image {
private:
    const std::string& file_path;
    u_int8_t* image_bytes;    
    int width;
    int height;
    int channels;
    bool contains_alpha;
    void validate_x_y(int x, int y) const;
    u_int8_t* get_pixel_location(int x, int y) const;
public:
    explicit Image(const std::string &file_path);
    Image(const Image& image);
    Image& operator=(const Image& image);
    ~Image();

    int get_shared_memory() const; //instead of passing it through to display.cpp, create an image in main and get fd from image itself.

    int get_height() const;

    int get_width() const;

    int get_channels() const;

    int get_red_value(int x, int y) const;

    int get_green_value(int x, int y) const;

    int get_blue_value(int x, int y) const;

    int get_alpha_value(int x, int y) const;


    void modify_pixel(int x, int y, int r, int g, int b);

};