#include "image.h"
#include "image_reader.h"

void compare(const std::string &firstFile, const std::string &secondFile) {
    std::ifstream first(firstFile);
    std::ifstream second(secondFile);
    bool same = true;
    if (first.is_open() && second.is_open()) {
        unsigned char value1;
        unsigned char value2;
        while (first >> value1 && second >> value2) {
            if (value1 != value2) {
                same = false;
            }
        }
    }
    else {
        std::cerr << "Error opening file." << std::endl;
    }
    if (same) {
        std::cout << "Passed!" << std::endl;
    }
    else {
        std::cout << "Failed!" << std::endl;
    }
}
int main() {

    // Initialize files

    image layer1, pattern1, layer2, car, pattern2, circles, layer_red, layer_green, layer_blue, text, text2;
    layer1.loadFile("input/layer1.tga");
    pattern1.loadFile("input/pattern1.tga");
    layer2.loadFile("input/layer2.tga");
    car.loadFile("input/car.tga");
    pattern2.loadFile("input/pattern2.tga");
    circles.loadFile("input/circles.tga");
    layer_red.loadFile("input/layer_red.tga");
    layer_green.loadFile("input/layer_green.tga");
    layer_blue.loadFile("input/layer_blue.tga");
    text.loadFile("input/text.tga");
    text2.loadFile("input/text2.tga");

    // Image tests



    cout << "Part 1: ";
    image temp = multiply(layer1, pattern1);
    temp.createFile("output/part1.tga");
    compare("examples/EXAMPLE_part1.tga", "output/part1.tga");
    temp = subtract(car, layer2);
    temp.createFile("output/part2.tga");

    cout << "Part 2: ";
    compare("examples/EXAMPLE_part2.tga", "output/part2.tga");

    cout << "Part 3: ";
    temp = multiply(layer1, pattern2);
    temp = screen(text, temp);
    temp.createFile("output/part3.tga");
    compare("output/part3.tga", "examples/EXAMPLE_part3.tga");

    // Part 4
    image temp2;
    cout << "Part 4: ";
    temp = multiply(layer2, circles);
    temp2 = subtract(pattern2, temp);
    temp2.createFile("output/part4.tga");
    compare("output/part4.tga", "examples/EXAMPLE_part4.tga");



    // Part 5
    cout << "Part 5: ";
    temp = overlay(layer1, pattern1);
    temp.createFile("output/part5.tga");
    compare("output/part5.tga", "examples/EXAMPLE_part5.tga");

    cout << "Part 6: ";
    temp = part6(car);
    temp.createFile("output/part6.tga");
    compare("output/part6.tga", "examples/EXAMPLE_part6.tga");

    cout << "Part 7: ";
    temp = part7(car);
    temp.createFile("output/part7.tga");
    compare("output/part7.tga", "examples/EXAMPLE_part7.tga");
    temp = part8(car, "red");
    temp.createFile("output/part8_r.tga");
    temp = part8(car, "green");
    temp.createFile("output/part8_g.tga");
    temp = part8(car, "blue");
    temp.createFile("output/part8_b.tga");

    cout << "Part 8 (red): ";
    compare("examples/EXAMPLE_part8_r.tga", "output/part8_r.tga");
    cout << "Part 8 (green): ";
    compare("examples/EXAMPLE_part8_g.tga", "output/part8_g.tga");
    cout << "Part 8 (blue): ";
    compare("examples/EXAMPLE_part8_b.tga", "output/part8_b.tga");

    cout << "Part 9: ";
    temp = part9(layer_red, layer_green, layer_blue);
    temp.createFile("output/part9.tga");
    compare("output/part9.tga", "examples/EXAMPLE_part9.tga");

    cout << "Part 10: ";
    temp = part10(text2);
    temp.createFile("output/part10.tga");
    compare("output/part10.tga", "examples/EXAMPLE_part10.tga");

    return 0;
}
