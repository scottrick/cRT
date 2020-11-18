#include <stdio.h>

#include <def.h>
#include <scene.h>
#include <cJSON.h>

Scene readScene(const char *filename) {
    printf("Reading scene %s...\n", filename);
    
    Vec3 cameraOrigin = { 0.0f, 0.0f, 0.0f };
    Vec3 cameraLookDir = { 0.0f, 0.0f, 1.0f };
    float cameraFov = PI / 4.5f; //40 degree camera angle
    Camera camera = { 
        cameraOrigin, 
        cameraLookDir,
        cameraFov 
    };
    
    Vec3 sphereCenter1 = { 1.0f, 0.0f, 10.0f };
    float sphereRadius1 = 2.0f;
    Color sphereColor1 = { 0.0f, 0.5f, 0.0f };
    Sphere sphere1 = {
        sphereCenter1,
        sphereRadius1,
        sphereColor1
    };

    Vec3 sphereCenter2 = { -4.0f, 3.0f, 14.0f };
    float sphereRadius2 = 7.0f;
    Color sphereColor2 = { 0.8f, 0.0f, 0.8f };
    Sphere sphere2 = {
        sphereCenter2,
        sphereRadius2,
        sphereColor2
    };
    
    Scene scene = { 1280, 800, camera, sphere1, sphere2 };
    
    cJSON *json = cJSON_Parse("{}");
    cJSON_Delete(json);

    return scene;
}
