#pragma once
#include "Image.h"

struct color{
    int r;
    int g;
    int b;
    int a;
};

class Color : public BaseImage {
private:
    color color_;
public:
    Color(const std::string &file_path, struct color color_);
};