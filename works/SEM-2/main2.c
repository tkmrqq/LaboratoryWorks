#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char toLower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

typedef struct character_t {
    int hp;
    int atk;
    int armor;
    char *name;
} character;

/*enum SortField {
    HP,
    ATK,
    ARMOR
};*/

character createCharacter(int hp, int atk, int armor, const char *name) {
    character c;
    c.hp = hp;
    c.atk = atk;
    c.armor = armor;
    c.name = (char *) malloc(strlen(name) + 1);//выделение памяти для хранения имени
    strcpy(c.name, name);                      //копирование имени в выделенную память
    return c;
}

void printCharacter(character c[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("===============\n");
        printf("Name: %s\nHP: %d\nAttack: %d\nArmor: %d\n", c[i].name, c[i].hp, c[i].atk, c[i].armor);
    }
}

//сравниваем хар-ки
int compareByHp(character *a, character *b) {
    return a->hp - b->hp;
}

int compareByAtk(character *a, character *b) {
    return a->atk - b->atk;
}

int compareByArmor(character *a, character *b) {
    return a->armor - b->armor;
}

int compareByName(character *a, character *b) {
    return strcmp(a->name, b->name);
}

char *getSortField() {
    static char SortField[5];
    printf("Enter field to sort by (hp, atk, armor, name):");
    scanf_s("%5s", SortField);
    for (int i = 0; i < 5; ++i) {
        SortField[i] = toLower(SortField[i]);
    }
    return SortField;
}

int chooseSort() {
    char *SortField = getSortField();
    if (strcmp(SortField, "hp") == 0) return 1;
    else if (strcmp(SortField, "atk") == 0)
        return 2;
    else if (strcmp(SortField, "armor") == 0)
        return 3;
    else if (strcmp(SortField, "name") == 0)
        return 4;
    return -1;
}

void sortCharacters(character characters[], int numChars) {
    int field = chooseSort();
    switch (field) {
        case 1: {
            qsort(characters, numChars, sizeof(character), (int (*)(const void *, const void *)) compareByHp);
            break;
        }
        case 2: {
            qsort(characters, numChars, sizeof(character), (int (*)(const void *, const void *)) compareByAtk);
            break;
        }
        case 3: {
            qsort(characters, numChars, sizeof(character), (int (*)(const void *, const void *)) compareByArmor);
            break;
        }
        case 4: {
            qsort(characters, numChars, sizeof(character), (int (*)(const void *, const void *)) compareByName);
            break;
        }
        default: {
            fprintf(stderr, "Invalid field type\n");
            exit(EXIT_FAILURE);
        }
    }
}

void Remove(character characters[], int *len) {
    char *name = malloc(0);
    printf("Input name: ");
    rewind(stdin);
    gets(name);

    for (int i = 0; i < *len; i++) {
        if (!strcmp(characters[i].name, name)) {

            for (int j = i; j < *len - 1; j++) {
                characters[j] = characters[j + 1];
            }
            (*len)--;
            break;
        }
    }
}

void menu() {
    printf("What do you want from my program?");
}

int main() {
    character characters[4];
    characters[0] = createCharacter(33465, 1692, 1111, "Hu tao");
    characters[1] = createCharacter(15444, 1281, 591, "Nahida");
    characters[2] = createCharacter(20867, 1347, 1089, "Raiden");
    characters[3] = createCharacter(15324, 2566, 741, "Ganyu");
    int n = sizeof(characters) / sizeof(characters[0]);
    sortCharacters(characters, n);
    printCharacter(characters, n);
    return 0;
}