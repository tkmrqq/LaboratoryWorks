#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int hp, atk, armor;
    char *name;
}character;

void initCharacter(){
    character squad[] = {{33465, 1692, 1111, "Hu Tao"},
              {15444, 1281, 591, "Nahida"},
              {20867, 1347, 1089, "Raiden"},
              {15324, 2566, 741, "Ganyu"}};
}

void printStruct(int n, character squad[]) {
    for (int i = 0; i < n; i++) {
        printf("Name:%s \t Hp: %d \t Atk: %d \t Armor: %d \n", squad[i].name, squad[i].hp, squad[i].atk, squad[i].armor);
    }
}

int main() {
    unsigned size;
    printf("Enter number of users: ");
    scanf_s("%d", &size);
    character* squad = malloc(size * sizeof(character));
    int n = sizeof(&squad) / sizeof(squad[0]);
    initCharacter();
    printStruct(n, squad);
    free(squad);
    return 0;
}

/*void menu() {
    printf("What do you want to print?");
    printf("How you want ot sort?\n1)by HP\t2)by ATK\t3)by armor\t4)by name\n");
}*/

/*
int main() {
    menu();
    character squad[];
    printArray(n, squad);
    return 0;
}*/
