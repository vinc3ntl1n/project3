#include "image.h"

image::image() {
    width = 0;
    height = 0;
}

image::image(Header header) {
    this->header = header;
    height = header.height;
    width = header.width;
}
short image::getHeight() {
    return height;
}

short image::getWidth()  {
    return width;
}
image::Header image::getHeader() {
    return this->header;
}

std::vector<Color> image::getVector() {
    return this->pixelvector;
}

void image::setVector(std::vector<Color>& vector) {
    this->pixelvector = vector;
}

const Color image::getPixel(int temp) {
    return pixelvector.at(temp);
}

void image::fileloader(const std::string& address) {
    std::ifstream file(address, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
        file.read(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
        file.read(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
        file.read(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
        file.read(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
        file.read(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
        file.read(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
        file.read(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
        file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
        file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
        file.read(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
        file.read(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));

        height = header.height;
        width = header.width;
        int size = height * width;

        for (int i = 0; i < size; i++) {
            Color a;
            file.read((char*)&a.blue, sizeof(a.blue));
            file.read((char*)&a.green, sizeof(a.green));
            file.read((char*)&a.red, sizeof(a.red));
            pixelvector.push_back(a);
        }
    }
    else {
        std::cerr << "Can't open the file." << std::endl;
    }
}
void image::filemaker(const std::string& address) {
    std::ofstream file(address, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
        file.write(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
        file.write(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
        file.write(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
        file.write(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
        file.write(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
        file.write(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
        file.write(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
        file.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
        file.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
        file.write(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
        file.write(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));

        for (int i = 0; i < pixelvector.size(); i++) {
            Color a = pixelvector.at(i);
            file.write((char*)&a.blue, sizeof(a.blue));
            file.write((char*)&a.green, sizeof(a.green));
            file.write((char*)&a.red, sizeof(a.red));
        }
    }
    else {
        std::cerr << "Can't make the file." << std::endl;
    }
}
