#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_CHARACTERS 10

struct character {
    int hp;
    int armor;
    int atk;
    char name[MAX_NAME_LENGTH];
};

struct character createCharacter(int hp, int atk, int armor, const char *name) {
    struct character c;
    c.hp = hp;
    c.atk = atk;
    c.armor = armor;
    c.name = (char *) malloc(strlen(name) + 1);// выделение памяти для хранения имени
    strcpy(c.name, name);                      // копирование имени в выделенную память
    return c;
}

int compare(const void *a, const void *b, void *fields) {
    const struct character *charA = (const struct character *)a;
    const struct character *charB = (const struct character *)b;
    int *sort_fields = (int *)fields;
    int result = 0;

    // Сначала сортируем по первому полю
    switch (sort_fields[0]) {
        case 1:  // сортировка по hp
            result = charA->hp - charB->hp;
            break;
        case 2:  // сортировка по atk
            result = charA->atk - charB->atk;
            break;
        case 3:  // сортировка по armor
            result = charA->armor - charB->armor;
            break;
        default:
            fprintf(stderr, "Invalid field type\n");
            exit(EXIT_FAILURE);
    }

    // Если первое поле равно, то сортируем по второму полю
    if (result == 0) {
        switch (sort_fields[1]) {
            case 1:  // сортировка по hp
                result = charA->hp - charB->hp;
                break;
            case 2:  // сортировка по atk
                result = charA->atk - charB->atk;
                break;
            case 3:  // сортировка по armor
                result = charA->armor - charB->armor;
                break;
            default:
                fprintf(stderr, "Invalid field type\n");
                exit(EXIT_FAILURE);
        }
    }

    return result;
}

void sort_characters(struct character *chars, int num_chars, int *sort_fields) {
    qsort(chars, num_chars, sizeof(struct character), compare, sort_fields);
}

void print_characters(struct character *chars, int num_chars) {
    printf("Characters:\n");
    for (int i = 0; i < num_chars; i++) {
        printf("Name: %s, HP: %d, Armor: %d, ATK: %d\n", chars[i].name, chars[i].hp, chars[i].armor, chars[i].atk);
    }
    printf("\n");
}

int get_sort_field() {
    int sort_field;
    printf("Enter field to sort by (1 - hp, 2 - atk, 3 - armor): ");
    scanf("%d", &sort_field);
    return sort_field;
}

int main() {
    struct character characters[MAX_CHARACTERS];
    characters[0] = createCharacter(33465, 1692, 1111, "Hu tao");
    characters[1] = createCharacter(15444, 1281, 591, "Nahida");
    characters[2] = createCharacter(20867, 1347, 1089, "Raiden");
    characters[3] = createCharacter(15324, 2566, 741, "Ganyu");
    int num_characters = 0;
    return 0;
}
