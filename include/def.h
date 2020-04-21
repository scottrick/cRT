#pragma once

static const float PI = 3.141592654f;

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Camera {
    Vec3 origin;        //the position of the camera
    Vec3 lookDir;       //the direction the camera is looking 
    float fov;          //the horizontal field of view (radians)
} Camera;

typedef struct Ray {
    Vec3 origin;        //the origin point of the ray
    Vec3 dir;           //direction the ray is traveling
} Ray;

typedef struct Color {
    float r;
    float g;
    float b;
} Color;

typedef struct Sphere {
    Vec3 center;        //center of the sphere
    float radius;
    Color color;
} Sphere;

typedef struct Scene {
    int imageWidth;
    int imageHeight;

    Camera camera;
    Sphere sphere;
} Scene;

typedef struct Intersection {
    float t1;
    float t2;
    Sphere *sphere;
} Intersection;

