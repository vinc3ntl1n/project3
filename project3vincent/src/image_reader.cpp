#include "image_reader.h"

unsigned char clamp(int value) {
    unsigned char clamped;
    if (value < 0) {
        clamped = 0;
    }
    else if (value > 255) {
        clamped = 255;
    }
    else {
        clamped = value;
    }
    return clamped;
}

float scale(float f) {
    f += 0.5f;
    return f;
}

image multiply(image &a, image &b) {
    vector<Color> aPixels = a.getPixelVec();
    vector<Color> bPixels = b.getPixelVec();
    image output = image(a.getHeader());
    vector<Color> tempVec;
    for (int i = 0; i < aPixels.size(); i++) {
        Color tempPixels;
        int blue = (int)(scale((aPixels[i].blueval * bPixels[i].blueval / 255.0f)));
        tempPixels.blue = (unsigned char)blue;
        int green = (int)(scale((aPixels[i].greenval * bPixels[i].greenval / 255.0f)));
        tempPixels.green = (unsigned char)green;
        int red = (int)(scale((aPixels[i].redval * bPixels[i].redval / 255.0f)));
        tempPixels.red = (unsigned char)red;
        tempVec.push_back(tempPixels);
    }
    output.setPixelVec(tempVec);
    return output;
}

image subtract(image &a, image &b) {
    vector<Color> aPixels = a.getPixelVec();
    vector<Color> bPixels = b.getPixelVec();
    image output = image(a.getHeader());
    vector<Color> tempVec;
    int result; //
    for (int i = 0; i < aPixels.size(); i++) {
        Color tempPixels;
        int blue = clamp(aPixels[i].blueval - bPixels[i].blueval);  // Subtracts each RGB value
        tempPixels.blue = (unsigned char)blue;
        int green = clamp(aPixels[i].greenval - bPixels[i].greenval);
        tempPixels.green = (unsigned char)green;
        int red = clamp(aPixels[i].redval - bPixels[i].redval);
        tempPixels.red = (unsigned char)red;
        tempVec.push_back(tempPixels);
    }
    output.setPixelVec(tempVec);
    return output;
}

image part6(image &a) {
    vector<Color> aPixels = a.getPixelVec();
    image output = image(a.getHeader());
    vector<Color> tempVec;
    int tempInt;
    for (int i = 0; i < aPixels.size(); i++) {
        Color tempColor;
        tempColor.blue = aPixels[i].blue;
        tempColor.red = aPixels[i].red;
        tempInt = aPixels[i].greenval + 200;
        tempInt = clamp(tempInt);
        tempColor.green = (unsigned char)tempInt;
        tempVec.push_back(tempColor);
    }
    output.setPixelVec(tempVec);
    return output;
}

image part7(image &a) {
    vector<Color> aPixels = a.getPixelVec();
    image output = image(a.getHeader());
    vector<Color> tempVec;
    int tempInt;
    for (int i = 0; i < aPixels.size(); i++) {
        Color tempColor;
        tempColor.green = aPixels[i].green;
        tempColor.blue = 0;
        float red = ((float)aPixels[i].redval / 255.0f * 4.0f);
        tempInt = (int)scale(red * 255.0f);
        tempInt = clamp(tempInt);
        tempColor.red = (unsigned char)tempInt;
        tempVec.push_back(tempColor);
    }
    output.setPixelVec(tempVec);
    return output;
}

image part8(image &a, const string &channel) {
    vector<Color> aPixels = a.getPixelVec();
    image output = image(a.getHeader());
    vector<Color> tempVec;
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
    output.setPixelVec(tempVec);
    return output;
}

image part9(image &red, image &green, image &blue) {
    vector<Color> redPixels = red.getPixelVec();
    vector<Color> greenPixels = green.getPixelVec();
    vector<Color> bluePixels = blue.getPixelVec();
    image output = image(red.getHeader());
    vector<Color> tempVec;
    for (int i = 0; i < redPixels.size(); i++) {
        Color tempColor;
        tempColor.red = redPixels[i].red;
        tempColor.green = greenPixels[i].green;
        tempColor.blue = bluePixels[i].blue;
        tempVec.push_back(tempColor);
    }
    output.setPixelVec(tempVec);
    return output;
}

image part10(image &a) {
    image output = image(a.getHeader());
    vector<Color> tempVec;
    int start = (a.getWidth() * a.getHeight()) - 1;
    for (start; start > -1; start--) {
        tempVec.push_back(a.getPixel(start));
    }
    output.setPixelVec(tempVec);
    return output;
}

image screen(image &a, image &b) {
    vector<Color> aPixels = a.getPixelVec();
    vector<Color> bPixels = b.getPixelVec();
    image output = image(a.getHeader());
    vector<Color> tempVec;
    for (int i = 0; i < aPixels.size(); i++) {
        Color tempColor;
        float blueA = (float)aPixels[i].blue / 255.0f;  // Sets A and B values for 1-(1-A)*(1-B)
        float blueB = (float)bPixels[i].blue / 255.0f;
        float greenA = (float)aPixels[i].green / 255.0f;
        float greenB = (float)bPixels[i].green / 255.0f;
        float redA = (float)aPixels[i].red / 255.0f;
        float redB = (float)bPixels[i].red / 255.0f;
        int outputBlue = (int)(255 * (1.0f - (1.0f - blueA) * (1.0f - blueB)) + 0.5f);
        int outputGreen = (int)(255 * (1.0f - (1.0f - greenA) * (1.0f - greenB)) + 0.5f);
        int outputRed = (int)(255 * (1.0f - (1.0f - redA) * (1.0f - redB)) + 0.5f);
        tempColor.blue = (unsigned char)clamp(outputBlue);
        tempColor.green = (unsigned char)clamp(outputGreen);
        tempColor.red = (unsigned char)clamp(outputRed);
        tempVec.push_back(tempColor);
    }
    output.setPixelVec(tempVec);
    return output;
}

image overlay(image &a, image &b) {
    vector<Color> aPixels = a.getPixelVec();
    vector<Color> bPixels = b.getPixelVec();
    image output = image(a.getHeader());
    vector<Color> tempVec;
    for (int i = 0; i < aPixels.size(); i++) {
        Color tempColor;
        int red;
        int green;
        int blue;

        // Checks each RGB value if B <= 0.5

        if (bPixels[i].redval < 128) { // If <= 0.5
            red = (int) (2.0f * (aPixels[i].redval * bPixels[i].redval / 255.0f) + 0.5f);
        } else {  // 1 - 2(1-A)(1-B)
            float redFloat = 1.0f - 2.0f * ((1.0f - (((float) (aPixels[i].redval) / 255.0f))) *
                                            ((1.0f - ((float) (bPixels[i].redval) / 255.0f))));
            red = (int)(redFloat * 255.0 + 0.5f);
        }
        tempColor.red = (unsigned char) red;
        if (bPixels[i].greenval < 128) {
            green = (int)(2.0f * (aPixels[i].greenval * bPixels[i].greenval / 255.0f) + 0.5f);
        } else {
            float greenFloat = 1.0f - 2.0f * ((1.0f - (((float) (aPixels[i].greenval) / 255.0f))) *
                                              ((1.0f - ((float) (bPixels[i].greenval) / 255.0f))));
            green = (int)(greenFloat * 255.0 + 0.5f);
        }
        tempColor.green = (unsigned char) green;
        if (bPixels[i].blueval< 128) {
            blue = (int) (2.0f * (aPixels[i].blueval * bPixels[i].blueval / 255.0f) + 0.5f);
        } else {
            float blueFloat = 1.0f - 2.0f * ((1.0f - (((float) (aPixels[i].blueval) / 255.0f))) *
                                             ((1.0f - ((float) (bPixels[i].blueval) / 255.0f))));
            blue = (int)(blueFloat * 255.0 + 0.5f);
        }
        tempColor.blue = (unsigned char) blue;
        tempVec.push_back(tempColor);
    }
    output.setPixelVec(tempVec);
    return output;
}