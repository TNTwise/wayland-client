#include "Color.h"
#include "Image.h"
#include <string>

using namespace std;

Color::Color(const string& file_name, struct color color_) : Image(file_name) {
    this->color_ = color_;
    // fill bytes with color
}