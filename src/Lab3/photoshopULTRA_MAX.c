#include <stdio.h>
#include <stdlib.h>

#pragma pack(1)

typedef struct {
    unsigned short int Type;
    unsigned int Size;
    unsigned short int Reserved1, Reserved2;
    unsigned int Offset;
} BMPFileHeader;

typedef struct {
    unsigned int Size;
    int Width, Height;
    unsigned short int Planes;
    unsigned short int BitsPerPixel;
    unsigned int Compression;
    unsigned int ImageSize;
    int XPixelsPerMeter, YPixelsPerMeter;
    unsigned int ColorsUsed, ColorsImportant;
} BMPInfoHeader;

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

void menu(int height, int width, unsigned char *pixels) {
    printf("1)Black and White\n2)Negative\n3)NIGGER\n");
    int key;
    scanf_s("%d", &key);
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
        default:
            return;
    }
}

void writeBMP(char* filename, int height, int width, unsigned char *pixels, int row_size){
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    FILE* outFile = fopen(filename, "wb");

    fwrite(&fileHeader, sizeof(BMPFileHeader), 1, outFile);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, outFile);

    for (int i = height - 1; i >= 0; i--) {
        fwrite(&pixels[i * width], 1, row_size, outFile);
    }

    fclose(outFile);
}

void readBMPBlocks(char* filename, int block_size) {
    FILE* file = fopen(filename, "rb");
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    fread(&fileHeader, sizeof(fileHeader), 1, file);
    fread(&infoHeader, sizeof(infoHeader), 1, file);

    int width = infoHeader.Width;
    int height = infoHeader.Height;
    int padding = (4 - (width * 3) % 4) % 4;
    int row_size = (width * 3 + padding);

    unsigned char* row = (unsigned char*)malloc(row_size * sizeof(unsigned char));
    int num_blocks = (height * row_size + block_size - 1) / block_size;
    for (int i = 0; i < num_blocks; i++) {
        int block_offset = i * block_size;
        int block_height = (block_offset + block_size > height) ? (height - block_offset) : block_size;
        for (int j = 0; j < block_height; j++) {
            fseek(file, fileHeader.Offset + (height - block_offset - j - 1) * row_size, SEEK_SET);
            fread(row, row_size, 1, file);
        }
    }
    menu(height, width, row);
    writeBMP("../output.bmp", height, width, row, row_size);
    fclose(file);
    free(row);
}


int main(){
    char* fileName = "../sample.bmp";
    readBMPBlocks(fileName, 1024);
    return 0;
}
