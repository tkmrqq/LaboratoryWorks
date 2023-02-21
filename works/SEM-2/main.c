#include "library.h"

int main() {
    character characters[4];
    characters[0] = createCharacter(33465, 1692, 1111, "Hu tao", PYRO);
    characters[1] = createCharacter(15444, 1281, 591, "Nahida", DENDRO);
    characters[2] = createCharacter(20867, 1347, 1089, "Raiden", ELECTRO);
    characters[3] = createCharacter(15324, 2566, 741, "Ganyu", CRYO);
    int n = sizeof(characters) / sizeof(characters[0]);
    menu(characters, n);
    return 0;
}