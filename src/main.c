#include <math.h>
#include <stdio.h>
#include <string.h>

#include <png_utility.h>
#include <scene.h>
#include <ray_util.h>
#include <vec3_util.h>

int main(int argc, char *argv[]) {
    
    char defaultFilename[] = "output.png";
    char *filename = defaultFilename;

    if (argc < 2) {
        printf("No output file specified, defaulting to %s.\n", filename);
    } 
    else {
        filename = argv[1];
    }

    Scene scene = readScene("test_scene.json");

    printf("scene size: %d, %d\n", scene.imageWidth, scene.imageHeight);

    unsigned char buffer[scene.imageWidth * scene.imageHeight * 3];
    memset(buffer, 0, sizeof(buffer));

    Ray rays[scene.imageWidth][scene.imageHeight];
    float fov = scene.camera.fov;
    float verticalFov = fov * scene.imageHeight / scene.imageWidth;

    float xRadians;
    float yRadians;
    float dx;
    float dy;

    /* Create all our rays. */
    for (int x = 0; x < scene.imageWidth; x++) {
        for (int y = 0; y < scene.imageHeight; y++) {
            xRadians = (((x + 0.5f) / scene.imageWidth) - 0.5f) * fov;
            yRadians = (((y + 0.5f) / scene.imageHeight) - 0.5f) * verticalFov;
            dx = tan(xRadians);
            dy = tan(yRadians);
 
            rays[x][y].origin = scene.camera.origin;
            rays[x][y].dir.x = dx;
            rays[x][y].dir.y = dy;
            rays[x][y].dir.z = 1.0f;
            normalizeVec3(&(rays[x][y].dir));
             
            Intersection intersect = findIntersection(&rays[x][y], &scene.sphere);
 
            if (intersect.sphere != 0) {
                buffer[y * scene.imageWidth * 3 + x * 3 + 0] = 0;
                buffer[y * scene.imageWidth * 3 + x * 3 + 1] = 0;
                buffer[y * scene.imageWidth * 3 + x * 3 + 2] = 0xff;
            } 
            else {
                buffer[y * scene.imageWidth * 3 + x * 3 + 0] = 0x11;
                buffer[y * scene.imageWidth * 3 + x * 3 + 1] = 0x11;
                buffer[y * scene.imageWidth * 3 + x * 3 + 2] = 0x11;
            }
        }
    }

    writeBufferToPNG(filename, scene.imageWidth, scene.imageHeight, buffer, "cRT generated image");

    return 0;
}
