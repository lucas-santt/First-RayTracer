#include "class/color.h"
#include "class/vec3.h"

#include <iostream>

int main() {

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int h = 0; h < image_height; h++) {
        std::clog << "\rScanlines remaining: " << image_height - h - 1 << ' ' << std::flush;
        for (int w = 0; w  < image_width; w++) {
            auto pixel_color = color(double(w)/(image_width-1), double(h)/(image_height-1), 0);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\nDone.\n";
}