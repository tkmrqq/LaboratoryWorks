#include "library.h"

int check() {
    int x;
    while (scanf_s("%d", &x) != 1 || x < 1 || getchar() != '\n') {
        fprintf(stderr, "Invalid input! Please try again.\n");
        rewind(stdin);
    }
    return x;
}

char toLower(char ch) {
    if (ch <= 'Z' && ch >= 'A')
        return ch - ('Z' - 'z');
    return ch;
}

void printCharacter(character *c, int n) {
    const char *ELEMENT_NAMES[] = {"CRYO", "PYRO", "ELECTRO", "DENDRO"};
    for (int i = 0; i < n; ++i) {
        printf("===============\n");
        printf("Name: %s\nHP: %d\nAttack: %d\nArmor: %d\nElement: %s\n", c[i].name, c[i].hp, c[i].atk, c[i].armor, ELEMENT_NAMES[c[i].element]);
    }
}

character *initArr(int size) {
    return (character *) malloc(size * sizeof(character));
}

//сравниваем хар-ки
int compareByHp(const character *a, const character *b) {
    return a->hp - b->hp;
}

int compareByAtk(const character *a, const character *b) {
    return a->atk - b->atk;
}

int compareByArmor(const character *a, const character *b) {
    if ((a->armor > b->armor) - (a->armor < b->armor) != 0)
        return (a->armor > b->armor) - (a->armor < b->armor);
    return a->atk - b->atk;
}

int compareByName(const character *a, const character *b) {
    return strcmp(a->name, b->name);
}

int compareByElement(const character *a, const character *b) {
    if (b->element < a->element) {
        return 1;
    } else if (a->element < b->element) {
        return -1;
    } else {
        return (b->element < a->element) - (a->element < b->element);
    }
}

int compareByNameHp(const character *a, const character *b) {
    if ((a->hp > b->hp) - (a->hp < b->hp) != 0) {
        return (a->hp > b->hp) - (a->hp < b->hp);
    } else {
        return strcmp(a->name, b->name);
    }
}

char *inputString() {
    int num = 256;
    int pos = 0;
    char *str = (char *) calloc(num, sizeof(char));
    char ch;
    while (1) {
        ch = (char) getchar();
        if (ch == '\n') {
            str[pos] = '\0';
            str = (char *) realloc(str, (pos + 1) * sizeof(char));
            return str;
        }

        str[pos] = ch;
        pos++;
        if (pos == 256)
            str = (char *) realloc(str, (pos + 1) * sizeof(char));
    }
}

void createCharacter(character *characters, int numCharacters) {
    for (int i = 0; i < numCharacters; i++) {
        printf("Input the characteristics of the [%d] character\n", i + 1);
        printf("Enter HP:");
        characters[i].hp = check();//&(characters+i)->hp)

        printf("Enter armor:");
        characters[i].armor = check();

        printf("Enter ATK:");
        characters[i].atk = check();

        printf("Enter name:");
        getchar();
        characters[i].name = inputString();

        printf("Enter element (PYRO, ELECTRO, DENDRO, CRYO):");
        char element[10];
        fgets(element, 10, stdin);
        if (strcmp(element, "PYRO\n") == 0) {
            characters[i].element = PYRO;
        } else if (strcmp(element, "ELECTRO\n") == 0) {
            characters[i].element = ELECTRO;
        } else if (strcmp(element, "DENDRO\n") == 0) {
            characters[i].element = DENDRO;
        } else if (strcmp(element, "CRYO\n") == 0) {
            characters[i].element = CRYO;
        } else {
            printf("Invalid element input. Setting to PYRO by default.\n");
            characters[i].element = PYRO;
        }
    }
}

char *getSortField() {
    static char SortField[5];
    printf("Enter field to sort by (hp, atk, armor, name, el, nmhp):");
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
    else if (strcmp(SortField, "nmhp") == 0)
        return 6;
    return -1;
}

void sortCharacters(character *characters, int numChars) {
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
        case 6: {
            qsort(characters, numChars, sizeof(character), (int (*)(const void *, const void *)) compareByNameHp);
            break;
        }
        default: {
            fprintf(stderr, "Invalid field type\n");
            exit(EXIT_FAILURE);
        }
    }
}

void Remove(character *characters, int *len) {
    char name[10];
    printf("Input name of structure:\n(available structures):\n");
    for (int i = 0; i < *len; ++i) {
        printf("[%d]: %s\t", (i + 1), characters[i].name);
    }
    printf("\n");
    rewind(stdin);
    scanf_s("%10s", name);

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


void initSize(int *size) {
    printf("How many structures do you want to input?\n");
    scanf_s("%d", size);
}

void menu(character *characters, int n) {
    int key;
    while (1) {
        printf("What do you want from my program?\n1) [Show structure]\t2) [Sort structure]\t3) [Delete structure]\t4) [Exit]\n");
        while (scanf_s("%d", &key) != 1 || key > 5 || key <= 0) {
            fprintf(stderr, "Invalid input!\n");
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
                exit(EXIT_FAILURE);
            }
        }
    }
}