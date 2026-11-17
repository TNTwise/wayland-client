#include <string>
#include <array>

struct raw_image {
    u_int8_t width;
    u_int8_t height;
    u_int8_t bbp;
    pixel *pixels;
};

struct pixel {
    u_int8_t red;
    u_int8_t blue;
    u_int8_t green;
};



class Image {
private:
    const std::string& file_path;
    raw_image* raw_image;

public:
    Image(const std::string &file_path);
    
    struct raw_image get_image() const;

    // struct pixel get_pixel_at(u_int8_t x, u_int8_t, y);

};