#include <Color.h>
#include <Image.h>
#include <string>

using namespace std;

Color::Color(const string& file_name, struct color color) : Image(file_name) {
    this->color = color;
    // fill bytes with color
}