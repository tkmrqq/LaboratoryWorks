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
    if (ch >= 'A'  &&  ch <= 'Z')
        return ch - ('Z' - 'z');
    return ch;
}

void printCharacter(character *c, int size) {
    const char *ELEMENT_NAMES[] = {"CRYO", "PYRO", "ELECTRO", "DENDRO"};
    for (int i = 0; i < size; ++i) {
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

int compareByAtkHp(const character *a, const character *b) {
    if (a->atk != b->atk) {
        return a->atk - b->atk;
    } else {
        return a->hp - b->hp;
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

void createCharacter(character *characters, int size, int k) {

    for (int i = k; i < size; i++) {
        printf("Input the characteristics of the [%d] character\n", i + 1);
        printf("Enter HP:");
        characters[i].hp = check();//&(characters+i)->hp)

        printf("Enter armor:");
        characters[i].armor = check();

        printf("Enter ATK:");
        characters[i].atk = check();

        printf("Enter name:");
        characters[i].name = inputString();

        printf("Enter element (PYRO, ELECTRO, DENDRO, CRYO):\n");
        char element[10];
        rewind(stdin);
        fgets(element, 10, stdin);
        for (int j = 0; j < 10; ++j) {
            element[j] = toLower(element[j]);
        }
        if (strcmp(element, "pyro\n") == 0) {
            characters[i].element = PYRO;
        } else if (strcmp(element, "electro\n") == 0) {
            characters[i].element = ELECTRO;
        } else if (strcmp(element, "dendro\n") == 0) {
            characters[i].element = DENDRO;
        } else if (strcmp(element, "cryo\n") == 0) {
            characters[i].element = CRYO;
        } else {
            printf("Invalid element input. Setting to PYRO by default.\n");
            characters[i].element = PYRO;
        }
    }
}

char *getSortField() {
    static char sortField[8];
    printf("Enter field to sort by (hp, atk, armor, name, el, nm*hp, atk*hp):");
    rewind(stdin);
    fgets(sortField, 8, stdin);
    for (int i = 0; i < 6; ++i) {
        sortField[i] = toLower(sortField[i]);
    }
    return sortField;
}

int chooseSort() {
    char *sortField = getSortField();
    if (strcmp(sortField, "hp\n") == 0)
        return 1;
    else if (strcmp(sortField, "atk\n") == 0)
        return 2;
    else if (strcmp(sortField, "armor\n") == 0)
        return 3;
    else if (strcmp(sortField, "name\n") == 0)
        return 4;
    else if (strcmp(sortField, "el\n") == 0)
        return 5;
    else if (strcmp(sortField, "nm*hp\n") == 0)
        return 6;
    else if(strcmp(sortField, "atk*hp\n") == 0)
        return 7;
    return -1;
}

void sortCharacters(character *characters, int size) {
    int field = chooseSort();
    switch (field) {
        case 1: {
            qsort(characters, size, sizeof(character), (int (*)(const void *, const void *)) compareByHp);
            break;
        }
        case 2: {
            qsort(characters, size, sizeof(character), (int (*)(const void *, const void *)) compareByAtk);
            break;
        }
        case 3: {
            qsort(characters, size, sizeof(character), (int (*)(const void *, const void *)) compareByArmor);
            break;
        }
        case 4: {
            qsort(characters, size, sizeof(character), (int (*)(const void *, const void *)) compareByName);
            break;
        }
        case 5: {
            qsort(characters, size, sizeof(character), (int (*)(const void *, const void *)) compareByElement);
            break;
        }
        case 6: {
            qsort(characters, size, sizeof(character), (int (*)(const void *, const void *)) compareByNameHp);
            break;
        }
        case 7:{
            qsort(characters, size, sizeof(character), (int (*)(const void *, const void *)) compareByAtkHp);
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

void addStructure(character **characters, int *size) {
    int temp = *size;
    int choice;
    printf("Hom many structures do you want to add?\n");
    choice = check();
    *size = *size + choice;
    *characters = (character *) realloc(*characters, (*size) * sizeof(character));
    createCharacter(*characters, *size, temp);
}

void initSize(int *size) {
    printf("How many structures do you want to input?\n");
    *size = check();
}

void menu(character *characters, int size) {
    int key;
    while (1) {
        printf("\nWhat do you want from my program?\n1) [Show structure]\t2) [Sort structure]\t3) [Delete structure]\t4) [Add structure]\t5) [Exit]\n");
        while (scanf_s("%d", &key) != 1 || key > 5 || key <= 0) {
            fprintf(stderr, "Invalid input!\n");
            rewind(stdin);
        }
        switch (key) {
            case 1: {
                printCharacter(characters, size);
                break;
            }
            case 2: {
                sortCharacters(characters, size);
                printCharacter(characters, size);
                break;
            }
            case 3: {
                Remove(characters, &size);
                printCharacter(characters, size);
                break;
            }
            case 4: {
                addStructure(&characters, &size);
                break;
            }
            case 5: {
                free(characters);
                rewind(stdin);
                exit(EXIT_SUCCESS);
            }
            default: {
                exit(EXIT_FAILURE);
            }
        }
    }
}