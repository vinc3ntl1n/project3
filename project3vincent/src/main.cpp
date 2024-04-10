#include "image.h"
#include "imagemodifer.h"

void test(const std::string &f1, const std::string &f2) {
    // Open the files in binary mode
    std::ifstream first(f1, std::ios::binary);
    std::ifstream second(f2, std::ios::binary);
    if (first.is_open() != true || second.is_open() != true) {
        std::cerr << "Can't open file." << std::endl;
        std::cout << "Failed!" << std::endl;
        return;
    }
    std::vector<char> firstFileContent((std::istreambuf_iterator<char>(first)), std::istreambuf_iterator<char>());
    std::vector<char> secondFileContent((std::istreambuf_iterator<char>(second)), std::istreambuf_iterator<char>());

    if (firstFileContent == secondFileContent) {
        std::cout << "Passed!" << std::endl;
    } else {
        std::cout << "Failed!" << std::endl;
    }
}

int main() {
    image layer1;
    image pattern1;
    image layer2;
    image car;
    image pattern2;
    image circles;
    image layer_red;
    image layer_green;
    image layer_blue;
    image text;
    image text2;

    layer1.fileloader("input/layer1.tga");
    pattern1.fileloader("input/pattern1.tga");
    layer2.fileloader("input/layer2.tga");
    car.fileloader("input/car.tga");
    pattern2.fileloader("input/pattern2.tga");
    circles.fileloader("input/circles.tga");
    layer_red.fileloader("input/layer_red.tga");
    layer_green.fileloader("input/layer_green.tga");
    layer_blue.fileloader("input/layer_blue.tga");
    text.fileloader("input/text.tga");
    text2.fileloader("input/text2.tga");

    std::cout << "Test #1...... ";
    image temp = multiplyBlend(layer1, pattern1);
    temp.filemaker("output/part1.tga");
    test("examples/EXAMPLE_part1.tga", "output/part1.tga");
    temp = subtractBlend(car, layer2);
    temp.filemaker("output/part2.tga");

    std::cout << "Test #2...... ";
    test("examples/EXAMPLE_part2.tga", "output/part2.tga");

    std::cout << "Test #3...... ";
    temp = multiplyBlend(layer1, pattern2);
    temp = screen(text, temp);
    temp.filemaker("output/part3.tga");
    test("output/part3.tga", "examples/EXAMPLE_part3.tga");

    // Part 4
    image temp2;
    std::cout << "Test #4...... ";
    temp = multiplyBlend(layer2, circles);
    temp2 = subtractBlend(temp,pattern2 );
    temp2.filemaker("output/part4.tga");
    test("output/part4.tga", "examples/EXAMPLE_part4.tga");

    // Part 5
    std::cout << "Test #5...... ";
    temp = overlay(layer1, pattern1);
    temp.filemaker("output/part5.tga");
    test("output/part5.tga", "examples/EXAMPLE_part5.tga");

    std::cout << "Test #6...... ";
    temp = p6(car);
    temp.filemaker("output/part6.tga");
    test("output/part6.tga", "examples/EXAMPLE_part6.tga");

    std::cout << "Test #7...... ";
    temp = p7(car);
    temp.filemaker("output/part7.tga");
    test("output/part7.tga", "examples/EXAMPLE_part7.tga");
    temp = p8(car, "red");
    temp.filemaker("output/part8_r.tga");
    temp = p8(car, "green");
    temp.filemaker("output/part8_g.tga");
    temp = p8(car, "blue");
    temp.filemaker("output/part8_b.tga");

    std::cout << "Test #8(red).. ";
    test("examples/EXAMPLE_part8_r.tga", "output/part8_r.tga");
    std::cout << "Test #8(blue). ";
    test("examples/EXAMPLE_part8_g.tga", "output/part8_g.tga");
    std::cout << "Test #8(green) ";
    test("examples/EXAMPLE_part8_b.tga", "output/part8_b.tga");

    std::cout << "Test #9...... ";
    temp = p9(layer_red, layer_green, layer_blue);
    temp.filemaker("output/part9.tga");
    test("output/part9.tga", "examples/EXAMPLE_part9.tga");

    std::cout << "Test #10...... ";
    temp = p10(text2);
    temp.filemaker("output/part10.tga");
    test("output/part10.tga", "examples/EXAMPLE_part10.tga");

    return 0;
}
