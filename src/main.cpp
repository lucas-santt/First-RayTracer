#include "class/color.h"
#include "class/ray.h"
#include "class/vec3.h"

#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 c_minus_q = center - r.origin();
    auto a = r.direction().length_squared();
    auto b = dot(r.direction(), c_minus_q);
    auto c = c_minus_q.length_squared() - radius*radius;
    auto delta = b*b - a*c; // Delta formula is modified

    if (delta < 0) {
        return -1;
    } else {
        // Smallest t (Assume that the sphere is in front of the camera)
        // x formula is modified here to lessen the number of multiplications
        return (b - std::sqrt(delta)) / a;
    }

    return (delta >= 0);
}

color ray_color(const ray& r) {
    point3 sphere_center(0, 0, -1);
    auto t = hit_sphere(sphere_center, 0.5, r);
    if(t > 0.0) {
        vec3 N = unit_vector(r.at(t) - sphere_center);
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    // Background color

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    // Apply Lerp to blend colors
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate image height, and ensure it is at least 1 pixel
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0; // Distance from the camera to the projection plane (viewport)
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0); // Horizontal, start at left
    auto viewport_v = vec3(0, -viewport_height, 0); // Vertical, start at top

    // Calculate the horizontal and vertical delta vectors (pixel spacing) fom pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    auto viewport_upper_left = camera_center 
                               - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // Pixel with coordinates (0, 0)
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int h = 0; h < image_height; h++) {
        std::clog << "\rScanlines remaining: " << image_height - h - 1 << ' ' << std::flush;
        for (int w = 0; w  < image_width; w++) {
            auto pixel_center = pixel00_loc + (w * pixel_delta_u) + (h * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\nDone.\n";
}