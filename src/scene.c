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
    
    Vec3 sphereCenter = { 1.0f, 0.0f, 10.0f };
    float sphereRadius = 2.0f;
    Color sphereColor = { 0.0f, 0.8f, 0.0f };
    Sphere sphere = {
        sphereCenter,
        sphereRadius,
        sphereColor
    };

    Scene scene = { 1280, 800, camera, sphere };
    
    cJSON *json = cJSON_Parse("{}");
    cJSON_Delete(json);

    return scene;
}
