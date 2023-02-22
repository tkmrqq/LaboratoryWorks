#include "library.h"

int main() {
    int size_add = additionalSize();
    character *characters = initArr(size_add);
    int size = createArray(characters);
    menu(characters, size);
    free(characters);
    return 0;
}