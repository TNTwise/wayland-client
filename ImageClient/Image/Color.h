#include <Image.h>

struct color{
    int r;
    int g;
    int b;
    int a;
};

class Color : public Image {
private:
    color color;
public:
    Color(const std::string &file_path, struct color color);
};