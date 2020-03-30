#include <stdio.h>
#include <string.h>

#include <png_utility.h>

int main(int argc, char *argv[]) {
    int size = 100;
    unsigned char buffer[size * size * 3];
    memset(buffer, 0, sizeof(buffer));

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            buffer[y * size * 3 + x * 3 + 1] = x; 
            buffer[y * size * 3 + x * 3 + 0] = y;
        }
    }

    writeBufferToPNG(argv[1], size, size, buffer, "hatfat");

    return 0;
}
