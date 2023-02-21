#include "library.h"

char toLower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

character createCharacter(int hp, int atk, int armor, const char *name, Element element) {
    character c;
    c.hp = hp;
    c.atk = atk;
    c.armor = armor;
    c.name = (char *) malloc(strlen(name) + 1);//выделение памяти для хранения имени
    strcpy_s(c.name, sizeof(c.name), name);    //копирование имени в выделенную память
    c.element = element;
    return c;
}

void printCharacter(character c[], int n) {
    const char *ELEMENT_NAMES[] = {"PYRO", "ELECTRO", "DENDRO", "CRYO"};
    for (int i = 0; i < n; ++i) {
        printf("===============\n");
        printf("Name: %s\nHP: %d\nAttack: %d\nArmor: %d\nElement: %s\n", c[i].name, c[i].hp, c[i].atk, c[i].armor, ELEMENT_NAMES[c[i].element]);
    }
}

//сравниваем хар-ки
int compareByHp(const character *a, const character *b) {
    return a->hp - b->hp;
}

int compareByAtk(const character *a, const character *b) {
    return a->atk - b->atk;
}

int compareByArmor(const character *a, const character *b) {
    return a->armor - b->armor;
}

int compareByName(const character *a, const character *b) {
    return strcmp(a->name, b->name);
}

int compareByElement(const character *a, const character *b) {
    return a->element - b->element;
}

char *getSortField() {
    static char SortField[5];
    printf("Enter field to sort by (hp, atk, armor, name, el):");
    scanf_s("%5s", SortField);
    for (int i = 0; i < 5; ++i) {
        SortField[i] = toLower(SortField[i]);
    }
    return SortField;
}

int chooseSort() {
    const char *SortField = getSortField();
    if (strcmp(SortField, "hp") == 0)
        return 1;
    else if (strcmp(SortField, "atk") == 0)
        return 2;
    else if (strcmp(SortField, "armor") == 0)
        return 3;
    else if (strcmp(SortField, "name") == 0)
        return 4;
    else if (strcmp(SortField, "el") == 0)
        return 5;
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
        case 5: {
            qsort(characters, numChars, sizeof(character), (int (*)(const void *, const void *)) compareByElement);
            break;
        }
        default: {
            fprintf(stderr, "Invalid field type\n");
            exit(EXIT_FAILURE);
        }
    }
}

void Remove(character characters[], int *len) {
    char name[6];
    printf("Input name of structure:\n(available structures):\n");
    for (int i = 0; i < *len; ++i) {
        printf("[%d]: %s\t", (i + 1), characters[i].name);
    }
    printf("\n");
    rewind(stdin);
    scanf_s("%6s", name);

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

void menu(character characters[], int n) {
    int key;
    while (1) {
        printf("What do you want from my program?\n1) [Show structure]\t2) [Sort structure]\t3) [Delete structure]\t4)[Exit]\n");
        while (scanf_s("%d", &key) != 1) {
            fprintf(stderr, "Invalid field type\n");
            rewind(stdin);
        }
        switch (key) {
            case 1: {
                printCharacter(characters, n);
                break;
            }
            case 2: {
                sortCharacters(characters, n);
                printCharacter(characters, n);
                break;
            }
            case 3: {
                Remove(characters, &n);
                printCharacter(characters, n);
                break;
            }
            case 4: {
                rewind(stdin);
                exit(EXIT_SUCCESS);
            }
            default: {
                fprintf(stderr, "Invalid input\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}