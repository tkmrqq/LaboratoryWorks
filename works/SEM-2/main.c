#include "library.h"

int main() {
    int size=5;
    character *characters;
    characters =(character*)malloc((size)*sizeof(character));
    characters[0] = createCharacter(33465, 1692, 1111, "HuTao", PYRO);
    characters[1] = createCharacter(15444, 1281, 591, "Nahida", DENDRO);
    characters[2] = createCharacter(20867, 1347, 1089, "Raiden", ELECTRO);
    characters[3] = createCharacter(15324, 2566, 741, "Ganyu", CRYO);
    characters[4] = createCharacter(16131, 2466, 741, "Ayaka", CRYO);
    menu(characters, size);
    free(characters);
    return 0;
}