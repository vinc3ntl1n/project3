cmake_minimum_required(VERSION 3.27)
project(project3vincent)

set(CMAKE_CXX_STANDARD 17)

add_executable(project3vincent src/main.cpp src/image.cpp src/image.h src/image_reader.cpp src/image_reader.h)
