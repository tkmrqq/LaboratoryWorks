#include "library.h"

int main() {
    int size = 0;
    initSize(&size);
    character *characters = initArr(size);
    createCharacter(characters, size);
    menu(characters, size);
    free(characters);
    return 0;
}