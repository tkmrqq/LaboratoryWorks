#include "BitMapPicture.h"

#define COLORS 255.0

int check(int x) {
    while (scanf_s("%d", &x) != 1 || x < 0 || x > 10) {
        rewind(stdin);
        fprintf(stderr, "ERROR!\n");
    }
    return x;
}

void convertToNegative(BMP *bmp, uint32_t height, uint32_t width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGB pixel = bmp->pixels[i][j];
            pixel.red = 255 - pixel.red;
            pixel.green = 255 - pixel.green;
            pixel.blue = 255 - pixel.blue;
            bmp->pixels[i][j] = pixel;
        }
    }
}

void convertToBW(BMP *bmp, uint32_t height, uint32_t width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGB pixel = bmp->pixels[y][x];
            uint8_t gray = (pixel.red + pixel.green + pixel.blue) / 3;
            pixel.red = gray;
            pixel.green = gray;
            pixel.blue = gray;
            bmp->pixels[y][x] = pixel;
        }
    }
}

void gammaCorrection(BMP *bmp, uint32_t height, uint32_t width) {
    double gamma;
    printf("Input a value of gamma:");
    scanf_s("%lf", &gamma);
    double gammaINV = 1 / gamma;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bmp->pixels[y][x].red = (uint8_t) (pow(bmp->pixels[y][x].red / COLORS, gammaINV) * COLORS);
            bmp->pixels[y][x].green = (uint8_t) (pow(bmp->pixels[y][x].green / COLORS, gammaINV) * COLORS);
            bmp->pixels[y][x].blue = (uint8_t) (pow(bmp->pixels[y][x].blue / COLORS, gammaINV) * COLORS);
        }
    }
}

const char *getFilePath() {
    char buffer[256];
    char *filePath = NULL;
    size_t filePathLen;

    while (1) {
        printf("Input file's path:");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Can't read file!\n");
            exit(EXIT_FAILURE);
        }
        char *token = strtok(buffer, "\n");
        if (strcmp(token + strlen(token) - 4, ".bmp") != 0) {
            printf("The file must have a .bmp extension\n");
            continue;
        }
        filePathLen = strlen(token) + 1;
        filePath = (char *) malloc(filePathLen);
        strncpy(filePath, token, filePathLen);
        break;
    }

    return filePath;
}

BMP *readBMP(const char *fileName) {
    BMP *bmp = malloc(sizeof(BMP));
    FILE *inputFile = fopen(fileName, "rb");
    if (inputFile == NULL) {
        printf("Error: Failed to open input file.");
        free(bmp);
        return NULL;
    }
    fread(&bmp->header, sizeof(BMPHeader), 1, inputFile);
    int width = bmp->header.width;
    int height = bmp->header.height;
    int bpp = bmp->header.bpp;
    printf("%d\n", bpp);

    if (bmp->header.bpp != 24) {
        printf("Error: File isn't 24 bits per pixel.");
        free(bmp);
        fclose(inputFile);
        return NULL;
    }


    if (bmp->header.compression) {
        printf("Error: Compression not supported.");
        free(bmp);
        fclose(inputFile);
        return NULL;
    }
    bmp->pixels = malloc(sizeof(RGB *) * height);
    for (int i = 0; i < height; i++) {
        bmp->pixels[i] = malloc(sizeof(RGB) * width);
    }

    uint32_t offset = bmp->header.offset;
    fseek(inputFile, offset, SEEK_SET);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fread(&bmp->pixels[i][j], sizeof(RGB), 1, inputFile);
        }
    }
    fclose(inputFile);
    return bmp;
}

void writeBMP(const char *fileName, const BMP *bmp) {
    FILE *outputFile = fopen(fileName, "wb");
    if (outputFile == NULL) {
        printf("Error: Failed to open output file.");
        return;
    }
    int width = bmp->header.width;
    int height = bmp->header.height;

    fwrite(&bmp->header, sizeof(BMPHeader), 1, outputFile);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&bmp->pixels[i][j], sizeof(RGB), 1, outputFile);
        }
    }

    int padding = (4 - (width * 3) % 4) % 4;
    for (int j = 0; j < padding; j++) {
        fputc(0x00, outputFile);
    }
    fclose(outputFile);
}

int compare(const void *a, const void *b) {
    const uint8_t *aa = (const uint8_t *) a;
    const uint8_t *bb = (const uint8_t *) b;
    return (*aa > *bb) - (*aa < *bb);
}

void medianFilter(const BMP *bmp, int window, uint32_t height, uint32_t width) {

    if (window % 2 == 0) {
        window++;
    }

    const int windowSize = window;

    int pad = windowSize / 2;

    RGB **pdPixels = malloc(sizeof(RGB *) * (height + 2 * pad));
    for (int i = 0; i < height + 2 * pad; i++) {
        pdPixels[i] = malloc(sizeof(RGB) * (width + 2 * pad));
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pdPixels[i + pad][j + pad] = bmp->pixels[i][j];
        }
    }

    for (int i = 0; i < pad; i++) {
        for (int j = 0; j < width + 2 * pad; j++) {
            pdPixels[i][j] = pdPixels[pad][j];
            pdPixels[height + 2 * pad - i - 1][j] = pdPixels[height + pad - 1][j];
        }
    }
    for (int i = 0; i < height + 2 * pad; i++) {
        for (int j = 0; j < pad; j++) {
            pdPixels[i][j] = pdPixels[i][pad];
            pdPixels[i][width + 2 * pad - j - 1] = pdPixels[i][width + pad - 1];
        }
    }

    for (int i = pad; i < height + pad; i++) {
        for (int j = pad; j < width + pad; j++) {
            uint8_t r[windowSize * windowSize];
            uint8_t g[windowSize * windowSize];
            uint8_t b[windowSize * windowSize];
            int k = 0;
            for (int ii = -pad; ii <= pad; ii++) {
                for (int jj = -pad; jj <= pad; jj++) {
                    r[k] = pdPixels[i + ii][j + jj].red;
                    g[k] = pdPixels[i + ii][j + jj].green;
                    b[k] = pdPixels[i + ii][j + jj].blue;
                    k++;
                }
            }

            qsort(r, windowSize * windowSize, sizeof(uint8_t), compare);
            qsort(g, windowSize * windowSize, sizeof(uint8_t), compare);
            qsort(b, windowSize * windowSize, sizeof(uint8_t), compare);

            bmp->pixels[i - pad][j - pad].red = r[windowSize * windowSize / 2];
            bmp->pixels[i - pad][j - pad].green = g[windowSize * windowSize / 2];
            bmp->pixels[i - pad][j - pad].blue = b[windowSize * windowSize / 2];
        }
    }

    for (int i = 0; i < height + 2 * pad; i++) {
        free(pdPixels[i]);
    }
    free(pdPixels);
}