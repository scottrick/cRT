typedef struct Scene {
    int imageWidth;
    int imageHeight;
} Scene;

Scene readScene(const char *filename);
