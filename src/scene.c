#include <stdio.h>

#include <scene.h>
#include <cJSON.h>

Scene readScene(const char *filename) {
    printf("Reading scene %s...\n", filename);
    
    Vec3 cameraOrigin = { 0.0f, 0.0f, 0.0f };
    Vec3 cameraLookPoint = { 0.0f, 0.0f, 10.0f };
    float cameraFov = 60.0f;
    Camera camera = { 
        cameraOrigin, 
        cameraLookPoint, 
        cameraFov 
    };
    
    Vec3 sphereCenter = { 2.0f, 0.0f, 22.0f };
    float sphereRadius = 8.0f;
    Color sphereColor = { 0.0f, 0.8f, 0.0f };
    Sphere sphere = {
        sphereCenter,
        sphereRadius,
        sphereColor
    };

    Scene scene = { 320, 240, camera, sphere };
    
    cJSON *json = cJSON_Parse("{}");
    cJSON_Delete(json);

    return scene;
}
