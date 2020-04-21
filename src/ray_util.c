#include <ray_util.h>
#include <vec3_util.h>

Intersection findIntersection(Ray *ray, Sphere *sphere) {    
    float a = dotProduct(&ray->dir, &ray->dir);

    Vec3 aMinusC = subVec3(&ray->origin, &sphere->center);
    float b = 2.0f * dotProduct(&ray->dir, &aMinusC);

    float c = dotProduct(&aMinusC, &aMinusC) - sphere->radius * sphere->radius;

    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f) {
        Intersection result = { 0.0f, 1.0f, 0 };
        return result;
    }
    else {
        Intersection result = { 0.0f, 1.0f, sphere };
        return result;
    }
}


