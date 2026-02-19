#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius): center(center), radius(std::fmax(0, radius)) {}

        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            vec3 c_minus_q = center - r.origin();
            auto a = r.direction().length_squared();
            auto b = dot(r.direction(), c_minus_q);
            auto c = c_minus_q.length_squared() - radius*radius;
            auto delta = b*b - a*c; // Delta formula is modified

            if (delta < 0) {
                return -1;

            auto sqrtd = std::sqrt(delta);

            // Root formula is modified here to lessen the number of multiplications
            auto root = (b - sqrtd) / a;
            if (root <= ray_tmin || root >= ray_tmax) {
                root = (b + sqrtd) / a;
                if (root <= ray_tmin || root >= ray_tmax)
                    return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }
        
    private:
        point3 center;
        double radius;
}

#endif