#include <stdio.h>
#include <string.h>

#include <png_utility.h>
#include <scene.h>

int main(int argc, char *argv[]) {

    Scene scene = readScene("test_scene.json");

    printf("scene size: %d, %d\n", scene.imageWidth, scene.imageHeight);

    unsigned char buffer[scene.imageWidth * scene.imageHeight * 3];
    memset(buffer, 0, sizeof(buffer));

    for (int x = 0; x < scene.imageWidth; x++) {
        for (int y = 0; y < scene.imageHeight; y++) {
            buffer[y * scene.imageWidth * 3 + x * 3 + 1] = x; 
            buffer[y * scene.imageWidth * 3 + x * 3 + 0] = y;
        }
    }

    writeBufferToPNG(argv[1], scene.imageWidth, scene.imageHeight, buffer, "hatfat");

    return 0;
}
