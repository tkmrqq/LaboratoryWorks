#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)

typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
    uint32_t dibSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xResolution;
    int32_t yResolution;
    uint32_t colors;
    uint32_t importantColors;
} BMPHeader;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB;

typedef struct BMPFile {
    BMPHeader header;
    RGB **pixels;
} BMP;

int check(int x);
void convertToNegative(BMP *bmp, uint32_t height, uint32_t width);
void convertToBW(BMP *bmp, uint32_t height, uint32_t width);
void gammaCorrection(BMP *bmp, uint32_t height, uint32_t width);
const char *getFilePath();
BMP *readBMP(const char *fileName);
void writeBMP(const char *fileName, const BMP *bmp);
int compare(const void *a, const void *b);
void medianFilter(const BMP *bmp, int windowSize, uint32_t height, uint32_t width);
void menu(BMP *bmp);

#pragma pack(pop)