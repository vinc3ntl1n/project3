//
// Created by 44vin on 4/9/2024.
//

#ifndef PROJECT3VINCENT_IMAGE_H
#define PROJECT3VINCENT_IMAGE_H
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct Color{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    int blueval;
    int greenval;
    int redval;
};

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
    const short getHeight() const;
    const short getWidth() const;
    vector<Color> getPixelVec();
    void setPixelVec(vector<Color> &vector);
    const Color getPixel(int x) const;
    Header getHeader();
    void loadFile(const string& filePath);
    void createFile(const string& filePath);
private:
    vector<Color> pixelVec;
    Header header;
    short width;
    short height;
};

#endif //PROJECT3VINCENT_IMAGE_H
