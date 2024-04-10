#include "imagemodifer.h"

unsigned char between(int i) {
    if (i < 0) {
        return 0;
    }
    if (i > 255){
        return 255;
    }
    return static_cast<unsigned char>(i);
}

image screen(image &a, image &b) {
    std::vector<Color> aPixels = a.getVector();
    std::vector<Color> bPixels = b.getVector();
    image output = image(a.getHeader());
    std::vector<Color> tempVec;

    for (size_t i = 0; i < aPixels.size(); i++) {
        float blueA = aPixels[i].blue / 255.0f;
        float blueB = bPixels[i].blue / 255.0f;
        float greenA = aPixels[i].green / 255.0f;
        float greenB = bPixels[i].green / 255.0f;
        float redA = aPixels[i].red / 255.0f;
        float redB = bPixels[i].red / 255.0f;

        Color tempColor;
        tempColor.blue = between(static_cast<int>((1 - (1 - blueA) * (1 - blueB)) * 255.0f + 0.5f));
        tempColor.green = between(static_cast<int>((1 - (1 - greenA) * (1 - greenB)) * 255.0f + 0.5f));
        tempColor.red = between(static_cast<int>((1 - (1 - redA) * (1 - redB)) * 255.0f + 0.5f));

        tempVec.push_back(tempColor);
    }

    output.setVector(tempVec);
    return output;
}

image overlay(image &a, image &b) {
    std::vector<Color> aPixels = a.getVector();
    std::vector<Color> bPixels = b.getVector();
    image output = image(a.getHeader());
    std::vector<Color> tempVec;
    if (aPixels.size() != bPixels.size()) {
        std::cerr << "Error: Images do not have the same size." << std::endl;
        return output;
    }
    for (int i = 0; i < aPixels.size(); ++i) {
        Color tempColor;
        int red, green, blue;

        if (bPixels[i].red < 128) {
            red = static_cast<int>(2.0f * (aPixels[i].red * bPixels[i].red / 255.0f) + 0.5f);
        } else {
            float redFloat = 1.0f - 2.0f * (1.0f - static_cast<float>(aPixels[i].red) / 255.0f) * (1.0f - static_cast<float>(bPixels[i].red) / 255.0f);
            red = static_cast<int>(redFloat * 255.0f + 0.5f);
        }
        if (bPixels[i].green < 128) {
            green = static_cast<int>(2.0f * (aPixels[i].green * bPixels[i].green / 255.0f) + 0.5f);
        } else {
            float greenFloat = 1.0f - 2.0f * (1.0f - static_cast<float>(aPixels[i].green) / 255.0f) * (1.0f - static_cast<float>(bPixels[i].green) / 255.0f);
            green = static_cast<int>(greenFloat * 255.0f + 0.5f);
        }
        if (bPixels[i].blue < 128) {
            blue = static_cast<int>(2.0f * (aPixels[i].blue * bPixels[i].blue / 255.0f) + 0.5f);
        } else {
            float blueFloat = 1.0f - 2.0f * (1.0f - static_cast<float>(aPixels[i].blue) / 255.0f) * (1.0f - static_cast<float>(bPixels[i].blue) / 255.0f);
            blue = static_cast<int>(blueFloat * 255.0f + 0.5f);
        }
        tempColor.red = static_cast<unsigned char>(std::min(red, 255));
        tempColor.green = static_cast<unsigned char>(std::min(green, 255));
        tempColor.blue = static_cast<unsigned char>(std::min(blue, 255));

        tempVec.push_back(tempColor);
    }

    output.setVector(tempVec);
    return output;
}

image multiplyBlend(image &a, image &b) {
    std::vector<Color> aPixels = a.getVector();
    std::vector<Color> bPixels = b.getVector();
    image output = image(a.getHeader());
    std::vector<Color> temp;
    Color tempColor;

    for (int i = 0; i < aPixels.size(); i++) {
        tempColor.blue = static_cast<unsigned char>((aPixels[i].blue * bPixels[i].blue) / 255.0f + 0.5f);  // Adding 0.5 for rounding
        tempColor.green = static_cast<unsigned char>((aPixels[i].green * bPixels[i].green) / 255.0f + 0.5f);
        tempColor.red = static_cast<unsigned char>((aPixels[i].red * bPixels[i].red) / 255.0f + 0.5f);
        temp.push_back(tempColor);
    }

    output.setVector(temp);
    return output;
}

image subtractBlend(image &a, image &b) {
    std::vector<Color> aPixels = a.getVector();
    std::vector<Color> bPixels = b.getVector();
    image output = image(a.getHeader());
    std::vector<Color> tempVec;

    for (int i = 0; i < aPixels.size(); i++) {
        Color tempPixels;
        tempPixels.blue = between(aPixels[i].blue - bPixels[i].blue);
        tempPixels.green = between(aPixels[i].green - bPixels[i].green);
        tempPixels.red = between(aPixels[i].red - bPixels[i].red);
        tempVec.push_back(tempPixels);
    }

    output.setVector(tempVec);
    return output;
}

image p6(image &a) {
    std::vector<Color> aPixels = a.getVector();
    image output(a.getHeader());
    std::vector<Color> tempVec;
    for (size_t i = 0; i < aPixels.size(); ++i) {
        Color tempColor;
        tempColor.blue = aPixels[i].blue;
        tempColor.red = aPixels[i].red;

        int greenWithOffset = static_cast<int>(aPixels[i].green) + 200;
        greenWithOffset = between(greenWithOffset);
        tempColor.green = static_cast<unsigned char>(greenWithOffset);

        tempVec.push_back(tempColor);
    }

    output.setVector(tempVec);
    return output;
}
image p7(image &a) {
    std::vector<Color> aPixels = a.getVector();
    image output = image(a.getHeader());
    std::vector<Color> tempVec;

    for (int i = 0; i < aPixels.size(); i++) {
        Color tempColor;
        tempColor.green = aPixels[i].green;
        tempColor.blue = 0;
        float redScaled = static_cast<float>(aPixels[i].red) / 255.0f * 4.0f;
        int tempInt = static_cast<int>(0.5f + (redScaled * 255.0f));
        tempInt = between(tempInt);
        tempColor.red = static_cast<unsigned char>(tempInt);
        tempVec.push_back(tempColor);
    }
    output.setVector(tempVec);
    return output;
}
image p8(image &a, const std::string &channel) {
    std::vector<Color> aPixels = a.getVector();
    image output = image(a.getHeader());
    std::vector<Color> tempVec;
    int tempInt;
    for (int i = 0; i < aPixels.size(); i++) {
        Color tempColor;
        unsigned char tempChar;
        if (channel == "blue") {
            tempChar = aPixels[i].blue;
        }
        else if (channel == "green") {
            tempChar = aPixels[i].green;
        }
        else if (channel == "red") {
            tempChar = aPixels[i].red;
        }
        tempColor.blue = tempChar;
        tempColor.green = tempChar;
        tempColor.red = tempChar;
        tempVec.push_back(tempColor);
    }
    output.setVector(tempVec);
    return output;
}
image p9(image &red, image &green, image &blue) {
    std::vector<Color> redPixels = red.getVector();
    std::vector<Color> greenPixels = green.getVector();
    std::vector<Color> bluePixels = blue.getVector();
    image output = image(red.getHeader());
    std::vector<Color> tempVec;
    for (int i = 0; i < redPixels.size(); i++) {
        Color tempColor;
        tempColor.red = redPixels[i].red;
        tempColor.green = greenPixels[i].green;
        tempColor.blue = bluePixels[i].blue;
        tempVec.push_back(tempColor);
    }
    output.setVector(tempVec);
    return output;
}
image p10(image &a) {
    image output = image(a.getHeader());
    std::vector<Color> tempVec;
    int start = (a.getWidth() * a.getHeight()) - 1;
    for (start; start > -1; start--) {
        tempVec.push_back(a.getPixel(start));
    }
    output.setVector(tempVec);
    return output;
}
