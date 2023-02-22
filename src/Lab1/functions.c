#include "library.h"

char toLower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

void printCharacter(character c[], int n) {
    const char *ELEMENT_NAMES[] = {"CRYO", "PYRO", "ELECTRO", "DENDRO"};
    for (int i = 0; i < n; ++i) {
        printf("===============\n");
        printf("Name: %s\nHP: %d\nAttack: %d\nArmor: %d\nElement: %s\n", c[i].name, c[i].hp, c[i].atk, c[i].armor, ELEMENT_NAMES[c[i].element]);
    }
}

character * initArr(int size)
{
    return (character *)malloc(size * sizeof(character));
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
    }
    else if (a->element < b->element) {
        return -1;
    }
    else {
        return (b->element < a->element) - (a->element < b->element);
    }
}

int compareByNameHp(const character * a, const character * b) {
    if ((a->hp > b->hp) - (a->hp < b->hp) != 0) {
        return (a->hp > b->hp) - (a->hp < b->hp);
    }
    else {
        return strcmp(a->name, b->name);
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
    else if(strcmp(SortField, "nmhp") == 0)
        return 6;
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
        case 6:{
            qsort(characters, numChars, sizeof(character), (int (*)(const void *, const void *)) compareByNameHp);
        }
        default: {
            fprintf(stderr, "Invalid field type\n");
            exit(EXIT_FAILURE);
        }
    }
}

void Remove(character characters[], int *len) {
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

char* get_string()
{
    int num = 256;
    char* string = (char*)calloc(num, sizeof(char));
    char ch;
    int pos = 0;
    while (1)
    {
        ch = getchar();
        if (ch == '\n')
        {
            string[pos] = '\0';
            string = (char*)realloc(string, (pos + 1) * sizeof(char));
            return string;
        }

        string[pos] = ch;
        pos++;
        if (pos == 256)
            string = (char*)realloc(string, (pos + 1) * sizeof(char));
    }
}

void get_int(int* x)
{
    while (!scanf_s("%d", x) || getchar() != '\n' || *x <= 0)
    {
        rewind(stdin);
        fprintf(stderr, "Invalid field type\n");
    }
}


int createArray(character characters[])
{
    int size = 0;
    int size_z = 256;
    printf("Input name of characters, to exit enter: \'s\'\n");
    char* z = (char*)calloc(size_z, sizeof(char));
    int i = 0;
    while (1)
    {
        char letter;
        letter = getchar();
        if (letter != '\n')
        {
            if (i < 256)
            {
                z[i] = letter;
                i++;
            }
            else
            {
                size_z++;
                z = (char*)malloc(size_z * sizeof(char));
                z[i] = letter;
                i++;
            }
        }
        else
        {
            z[i] = '\0';
            if (z[0] == 's' && z[1] == '\0')
            {
                break;
            }
            characters[size].name = z;
            printf("Input hp of character:");
            get_int(&characters[size].hp);
            printf("Input attack of character:");
            get_int(&characters[size].atk);
            printf("Input armor of character:");
            get_int(&characters[size].armor);
            printf("Choose element of character:(0-Cryo\t1-Pyro\t2-Electro\t3-Dendro)\n");
            scanf_s("%d", &characters[size].element);
//            z = (char*)calloc(256, sizeof(char));
            size++;
            printf("\nInput name of characters, to exit enter: \'s\'");
            i = 0;
        }
    }
    return size;
}

/*character *createArray(int size) {
    character *characters = malloc(sizeof(character) * size);

    for (int i = 0; i < size; i++) {
        printf("Input name of [%d] character: ", i + 1);
        scanf_s("%s", characters[i].name);

        printf("Input HP of [%d] character : ", i + 1);
        scanf_s("%d", &characters[i].hp);

        printf("Input attack of [%d] character : ", i + 1);
        scanf_s("%d", &characters[i].atk);

        printf("Input armor of [%d] character : ", i + 1);
        scanf_s("%d", &characters[i].armor);

        printf("Input element of [%d] character (0-CRYO, 1-PYRO, 2-ELECTRO, 3-DENDRO): ", i + 1);
        scanf_s("%d", &characters[i].element);
    }

    return characters;
}*/

int additionalSize() {
    printf("How many structures do you want to input?\n");
    int size = scanf_s("%d", &size);
    return size;
}

void menu(character characters[], int n) {
    int key;
    while (1) {
        printf("What do you want from my program?\n1) [Show structure]\t2) [Sort structure]\t3) [Delete structure]\t4) [Add Structure]\t5) [Exit]\n");
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
                break;
            }
            case 5: {
                rewind(stdin);
                exit(EXIT_SUCCESS);
            }
            default: {
                exit(EXIT_FAILURE);
            }
        }
    }
}