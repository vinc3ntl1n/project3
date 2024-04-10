//
// Created by 44vin on 4/9/2024.
//

#include "image.h"

image::image() {  // Default constructor
    width = 0;
    height = 0;
}
image::image(Header head) {  // If header is known
    this->header = head;
    height = head.height;
    width = head.width;
}

const short image::getHeight() const {
    return height;
}

const short image::getWidth() const {
    return width;
}

image::Header image::getHeader() {
    return this->header;
}

vector<Color> image::getPixelVec() {
    return this->pixelVec;
}
void image::setPixelVec(vector<Color> &vector) {
    this->pixelVec = vector;
}
const Color image::getPixel(int x) const {
    return pixelVec.at(x);
}

void image::loadFile(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (file.is_open()) {
        file.read(&header.idLength, sizeof(header.idLength));
        file.read(&header.colorMapType, sizeof(header.colorMapType));
        file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
        file.read((char*)&header.yOrigin, sizeof(header.yOrigin));
        file.read((char*)&header.width, sizeof(header.width));
        file.read((char*)&header.height, sizeof(header.height));
        file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));
        height = header.height;
        width = header.width;
        int size = height * width;

        // Reads pixel data

        for (int i = 0; i < size; i++) {
            Color a;
            file.read((char*)&a.blue, sizeof(a.blue));
            file.read((char*)&a.green, sizeof(a.green));
            file.read((char*)&a.red, sizeof(a.red));
            a.blueval = (int)a.blue;
            a.greenval = (int)a.green;
            a.redval = (int)a.red;
            pixelVec.push_back(a);
        }
    }
    else {
        cerr << "Failed to open file." << endl;
    }
}

void image::createFile(const string& filePath) {
    ofstream file(filePath, ios::binary);
    if (file.is_open()) {
        file.write(&header.idLength, sizeof(header.idLength));
        file.write(&header.colorMapType, sizeof(header.colorMapType));
        file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        file.write((char*)&header.width, sizeof(header.width));
        file.write((char*)&header.height, sizeof(header.height));
        file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

        // Writes pixel data

        for (int i = 0; i < pixelVec.size(); i++) {
            Color a = pixelVec.at(i);
            file.write((char*)&a.blue, sizeof(a.blue));
            file.write((char*)&a.green, sizeof(a.green));
            file.write((char*)&a.red, sizeof(a.red));
        }
    }
    else {
        cerr << "Failed to open file." << endl;
    }
}
