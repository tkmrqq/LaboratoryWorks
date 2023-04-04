#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma pack(1)

typedef struct {
    unsigned int type;
    unsigned int size;
    unsigned int reversed1, reversed2;
    unsigned int offset;
} Header;

typedef struct {
    unsigned int Size;
    int Width, Height;
    unsigned int Planes;
    unsigned int BitsPerPixel;
    unsigned int Compression;
    unsigned int ImageSize;
    int XPixelPerMeter, YPixelPerMeter;
    unsigned int ColorUsed;
} InfoHeader;

typedef struct {
    unsigned char r, g, b, junk;
} COLORINDEX;

int check(int x){
    while (scanf_s("%d", &x) != 1 ){
        rewind(stdin);
        fprintf(stderr, "ERROR!");
    }
    return x;
}

void convertToNegative(int height, int width, unsigned char *pixels) {
    for (int i = 0; i < height * width * 3; i++) {
        pixels[i] = 255 - pixels[i];
    }
}

void convertToBW(int height, int width, unsigned char *pixels) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            unsigned char r = pixels[index + 2];
            unsigned char g = pixels[index + 1];
            unsigned char b = pixels[index];
            unsigned char gray = 0.299 * r + 0.587 * g + 0.114 * b;
            pixels[index + 2] = gray;
            pixels[index + 1] = gray;
            pixels[index] = gray;
        }
    }
}

void gammaCorrection(int height, int width, unsigned char *pixels) {
    double gamma = 1.2;
    printf("Input a value of gamma:");
    scanf_s("%lf", &gamma);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            double r = pow((double)pixels[index+2] / 255.0, gamma) * 255.0;
            double g = pow((double)pixels[index+1] / 255.0, gamma) * 255.0;
            double b = pow((double)pixels[index] / 255.0, gamma) * 255.0;
            pixels[index + 2] = (unsigned char)r;
            pixels[index + 1] = (unsigned char)g;
            pixels[index] = (unsigned char)b;
        }
    }
}

void menu(int height, int width, unsigned char *pixels) {
    printf("1)Black and White\n2)Negative\n3)NIGGER\n4)Gamma-correction\n");
    int key = 0;
    key = check(key);
    switch (key) {
        case 1:
            convertToBW(height, width, pixels);
            break;
        case 2:
            convertToNegative(height, width, pixels);
            break;
        case 3:
            convertToBW(height, width, pixels);
            convertToNegative(height, width, pixels);
            break;
        case 4:
            gammaCorrection(height, width, pixels);
            break;
        default:
            return;
    }
}

int main() {
    FILE *file = fopen("../sample.bmp", "rb");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return -1;
    }
    int blockSize = 1024;
    Header fileHeader;
    InfoHeader infoHeader;
    fread(&fileHeader, sizeof(fileHeader), 1, file);
    fread(&infoHeader, sizeof(infoHeader), 1, file);

    int width = infoHeader.Width;
    int height = infoHeader.Height;
    int padding = (4 - (width * 3) % 4) % 4;
    unsigned char* pixels = (unsigned char*)malloc(width * height * 3);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width + x) * 3;
            fread(&pixels[index + 2], 1, 1, file);
            fread(&pixels[index + 1], 1, 1, file);
            fread(&pixels[index], 1, 1, file);
        }
        fseek(file, padding, SEEK_CUR);
    }
    fclose(file);

    menu(height, width, pixels);

    FILE *outputFile = fopen("../output.bmp", "wb");
    fwrite(&fileHeader, sizeof(fileHeader), 1, outputFile);
    fwrite(&infoHeader, sizeof(infoHeader), 1, outputFile);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            fwrite(&pixels[index + 2], 1, 1, outputFile);
            fwrite(&pixels[index + 1], 1, 1, outputFile);
            fwrite(&pixels[index], 1, 1, outputFile);
        }
        for (int i = 0; i < padding; i++) {
            fputc(0x00, outputFile);
        }
    }
    fclose(outputFile);
    free(pixels);
    return 0;
}
