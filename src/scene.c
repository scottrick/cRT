#include <scene.h>
#include <cJSON.h>

Scene readScene(const char *filename) {
    Scene scene = { 120, 60 };
    
    cJSON *json = cJSON_Parse("{}");
    cJSON_Delete(json);

    return scene;
}
