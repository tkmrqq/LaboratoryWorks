#include "library.h"

int main() {
    int size = 0;
    initSize(&size);
    character *characters = initArr(size);
    createCharacter(characters, size, 0);
    menu(characters, size);
    return 0;
}