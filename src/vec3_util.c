#include <vec3_util.h>

#include <math.h>
#include <stdio.h>

void normalizeVec3(Vec3 *vec3) {
   float value = 
       vec3->x * vec3->x +
       vec3->y * vec3->y +
       vec3->z * vec3->z;

   value = sqrt(value);

   vec3->x /= value;
   vec3->y /= value;
   vec3->z /= value;
}

void printVec3(Vec3 *vec3) {
    printf("Vec3[0x%p] (%0.3f, %0.3f, %0.3f)\n", 
            (void *) vec3, 
            (double) vec3->x, 
            (double) vec3->y, 
            (double) vec3->z);
}

Vec3 addVec3(Vec3 *v1, Vec3 *v2) {
    Vec3 result = {
            v1->x + v2->x,
            v1->y + v2->y,
            v1->z + v2->z
    };

    return result;
}

Vec3 subVec3(Vec3 *v1, Vec3 *v2) {
    Vec3 result = {
            v1->x - v2->x,
            v1->y - v2->y,
            v1->z - v2->z
    };

    return result;
}

float dotProduct(Vec3 *v1, Vec3 *v2) {
    return 
        v1->x * v2->x +
        v1->y * v2->y +
        v1->z * v2->z;
}

