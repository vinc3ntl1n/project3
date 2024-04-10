#ifndef PROJECT3VINCENT_IMAGE_H
#define PROJECT3VINCENT_IMAGE_H
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "Color.h"

class image {
public:
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    image();
    image(Header head);
    Header getHeader();
    short getHeight();
    short getWidth();
    std::vector<Color> getVector();
    void setVector(std::vector<Color> &vector);
    const Color getPixel(int x);
    //setpixel,getVector ill write if I need to
    void fileloader(const std::string& filePath);
    void filemaker(const std::string& filePath);

private:
    short width;
    short height;
    std::vector<Color> pixelvector;
    Header header;
};

#endif //PROJECT3VINCENT_IMAGE_H
