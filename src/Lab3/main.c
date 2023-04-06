#include "BitMapPicture.h"

void menu(BMP *bmp) {
    uint32_t width = bmp->header.width;
    uint32_t height = bmp->header.height;
    printf("1)Black and White\n2)Negative\n3)B&W+Neg\n4)Gamma-correction\n5)Median Filter\n");
    int key = 0;
    int win = 0;
    key = check(key);
    switch (key) {
        case 1:
            convertToBW(bmp, height, width);
            break;
        case 2:
            convertToNegative(bmp, height, width);
            break;
        case 3:
            convertToBW(bmp, height, width);
            convertToNegative(bmp, height, width);
            break;
        case 4:
            gammaCorrection(bmp, height, width);
            break;
        case 5:
            printf("Median value=");
            win = check(win);
            medianFilter(bmp, win, height, width);
            break;
        default:
            return;
    }
}

int main() {
    const char *fileName = getFilePath();
    BMP *bmp = readBMP(fileName);
    menu(bmp);
    writeBMP("../output.bmp", bmp);
    free(bmp->pixels);
    free(bmp);
    return 0;
}