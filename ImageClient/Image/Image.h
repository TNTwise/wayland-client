#include <string>
#include <array>




class Image {
private:
    const std::string& file_path;
    u_int8_t* image_bytes;    
    int width;
    int height;
    int channels;
public:
    Image(const std::string &file_path);
    

    void write_to_anon_file(int fb) const;

    int get_height() const;

    // struct pixel get_pixel_at(u_int8_t x, u_int8_t, y);

};