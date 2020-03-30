#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <png.h>

int writeBuffer(char *filename, int width, int height, const unsigned char *buffer, char *title);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Please specify output file.\n");
        return 1;
    }

    /* Dimensions of the test image */
    int width = 32;
    int height = 32;

    printf("Creating test image...\n");
    unsigned char buffer[width * height * 3];
    memset(buffer, 0, sizeof(buffer));

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            buffer[y * width * 3 + x * 3 + 1] = 255; 
        }
    }

    int result = writeBuffer(argv[1], width, height, buffer, "hatfat test image");

    if (result) {
        fprintf(stderr, "Error writing png file.\n");    
    }
    else {
        printf("Success!\n");
    }
    
    return result;
}

/* 
 Expects a buffer with 3 bytes per pixel (RGB).
 */
int writeBuffer(char *filename, int width, int height, const unsigned char *buffer, char *title) {
    int code = 0;
    FILE *fp = NULL;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s.\n", filename);
        code = 1;
        goto finalise;
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        fprintf(stderr, "Could not allocate png write struct.\n");
        code = 1;
        goto finalise;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fprintf(stderr, "Could not allocate png info struct.\n");
        code = 1;
        goto finalise;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "Error during png creation.\n");
        code = 1;
        goto finalise;
    }

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, 
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    if (title != NULL) {
        png_text title_text;
        title_text.compression = PNG_TEXT_COMPRESSION_NONE;
        title_text.key = "Title";
        title_text.text = title;
        png_set_text(png_ptr, info_ptr, &title_text, 1);
    }

    png_write_info(png_ptr, info_ptr);

    int x, y;
    for (y = 0; y < height; y++) {
        png_write_row(png_ptr, &buffer[y * width * 3]); 
    }

    png_write_end(png_ptr, NULL);

    finalise:
    if (fp != NULL) {
        fclose(fp);
    }

    if (info_ptr != NULL) {
        png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    }

    if (png_ptr != NULL) {
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    }

    return code;
}

