#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char toLower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

struct character {
    int hp;
    int atk;
    int armor;
    char *name;
};

/*enum SortField {
    HP,
    ATK,
    ARMOR
};*/

struct character createCharacter(int hp, int atk, int armor, const char *name) {
    struct character c;
    c.hp = hp;
    c.atk = atk;
    c.armor = armor;
    c.name = (char *) malloc(strlen(name) + 1);// выделение памяти для хранения имени
    strcpy(c.name, name);                      // копирование имени в выделенную память
    return c;
}

void printCharacter(struct character c) {
    printf("Name: %s\n", c.name);
    printf("HP: %d\n", c.hp);
    printf("Attack: %d\n", c.atk);
    printf("Armor: %d\n", c.armor);
}

char *getSortField() {
    static char SortField[5];
    printf("Enter field to sort by (hp, atk, armor, name): ");
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
        printf("You can't sort by name yet :(\n");
    return -1;
}

int compare(const void *a, const void *b, int field) {
    const struct character *charA = (const struct character *) a;
    const struct character *charB = (const struct character *) b;
    int result;
    switch (field) {
        case 1:// сортировка по hp
            result = charA->hp - charB->hp;
            break;
        case 2:// сортировка по atk
            result = charA->atk - charB->atk;
            break;
        case 3:// сортировка по armor
            result = charA->armor - charB->armor;
            break;
        default:
            fprintf(stderr, "Invalid field type\n");
            exit(EXIT_FAILURE);
    }
    return result;
}

void sort_characters(struct character characters[], int numChars) {
    int field = chooseSort();
//    qsort(characters, numChars, sizeof(struct character), (int (*)(const void *, const void *)) compare);
    qsort(characters, numChars, sizeof(struct character), compare, &field);

}

int main() {
    struct character characters[4];
    characters[0] = createCharacter(33465, 1692, 1111, "Hu tao");
    characters[1] = createCharacter(15444, 1281, 591, "Nahida");
    characters[2] = createCharacter(20867, 1347, 1089, "Raiden");
    characters[3] = createCharacter(15324, 2566, 741, "Ganyu");
    int n = sizeof(characters) / sizeof(characters[0]);
    sort_characters(characters, n);
    for (int i = 0; i < 4; ++i) {
        printf("===============\n");
        printCharacter(characters[i]);
    }
    return 0;
}