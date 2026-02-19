#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // [0, 1] -> [0, 255]
    // Utilizamos 255.999 pelo truncamento da conversão p/int: 
    // 255 * 0.9999 = 254.9997 -> 254, e não 255
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);
    
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif