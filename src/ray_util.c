#include <ray_util.h>
#include <vec3_util.h>

#include <math.h>

/* Returns the first intersection with the given sphere */
Intersection findIntersection(Ray *ray, Sphere *sphere) {    
    float a = dotProduct(&ray->dir, &ray->dir);

    Vec3 aMinusC = subVec3(&ray->origin, &sphere->center);
    float b = 2.0f * dotProduct(&ray->dir, &aMinusC);

    float c = dotProduct(&aMinusC, &aMinusC) - sphere->radius * sphere->radius;

    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f) {
        Intersection result = { 0.0f, 0 };
        return result;
    }
    else {
        float t1 = (-b - (float)sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + (float)sqrt(discriminant)) / (2.0f * a);
        
        if (t1 < 0.0f && t2 < 0.0f) {
            /* both intersections happened behind the ray */
            Intersection result = { 0.0f, 0 };
            return result;
        }

        if (t1 < 0.0f) {
            Intersection result = { t2, sphere };
            return result;
        }

        if (t2 < 0.0f) {
            Intersection result = { t1, sphere };
            return result;
        }

        /* both times are positive, so use the earliest */
        if (t1 < t2) {
            Intersection result = { t1, sphere };
            return result;
        }
        else {
            Intersection result = { t2, sphere };
            return result;
        }
    }
}

