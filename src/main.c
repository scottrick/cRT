#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <color.h>
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

    printf("Scene size is (%d, %d).\n", scene.imageWidth, scene.imageHeight);
    clock_t time  = clock();

    unsigned char buffer[scene.imageWidth * scene.imageHeight * 3];
    memset(buffer, 0, sizeof(buffer));

    Ray *rays = malloc(scene.imageWidth * scene.imageHeight * sizeof(Ray));
    
    float fov = scene.camera.fov;
    float verticalFov = fov * scene.imageHeight / scene.imageWidth;

    float xRadians;
    float yRadians;
    float dx;
    float dy;
    int pos = 0;

    /* Create all our rays. */
    for (int x = 0; x < scene.imageWidth; x++) {
        for (int y = 0; y < scene.imageHeight; y++) {
            xRadians = (((x + 0.5f) / scene.imageWidth) - 0.5f) * fov;
            yRadians = -(((y + 0.5f) / scene.imageHeight) - 0.5f) * verticalFov;
            dx = tan(xRadians);
            dy = tan(yRadians);
            pos = y * scene.imageWidth + x;
 
            rays[pos].origin = scene.camera.origin;
            rays[pos].dir.x = dx;
            rays[pos].dir.y = dy;
            rays[pos].dir.z = 1.0f;
            normalizeVec3(&(rays[pos].dir));
             
            Intersection intersect1 = findIntersection(&rays[pos], &scene.sphere1);
            Intersection intersect2 = findIntersection(&rays[pos], &scene.sphere2);
 
            Intersection *pClosestIntersection = 0;
            if (intersect1.sphere != 0 && intersect2.sphere == 0) {
                pClosestIntersection = &intersect1;
            }
            else if (intersect2.sphere != 0 && intersect1.sphere == 0) {
                pClosestIntersection = &intersect2;
            }
            else if (intersect1.sphere != 0 && intersect2.sphere != 0) {
                /* both intersected */
                if (intersect1.time < intersect2.time) {
                    pClosestIntersection = &intersect1;
                }
                else {
                    pClosestIntersection = &intersect2;
                }
            }

            if (pClosestIntersection != 0) {
                buffer[y * scene.imageWidth * 3 + x * 3 + 0] =
                    colorToChar(pClosestIntersection->sphere->color.r); 
                buffer[y * scene.imageWidth * 3 + x * 3 + 1] =
                    colorToChar(pClosestIntersection->sphere->color.g);
                buffer[y * scene.imageWidth * 3 + x * 3 + 2] = 
                    colorToChar(pClosestIntersection->sphere->color.b);
            } 
            else {
                buffer[y * scene.imageWidth * 3 + x * 3 + 0] = 0x11;
                buffer[y * scene.imageWidth * 3 + x * 3 + 1] = 0x11;
                buffer[y * scene.imageWidth * 3 + x * 3 + 2] = 0x11;
            }
        }
    }

    writeBufferToPNG(filename, scene.imageWidth, scene.imageHeight, buffer, "cRT generated image");
    
    time = clock() - time; 
    printf("Image creation took %f seconds.\n", ((double)time) / CLOCKS_PER_SEC);

    return 0;
}

