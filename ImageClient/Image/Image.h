#pragma once
#include <string>
#include <array>
#include "BaseImage.h"


class Image : public BaseImage{
   
public:
    Image(const std::string &file_path);
    int get_shared_memory() const; //instead of passing it through to display.cpp, create an image in main and get fd from image itself.

};