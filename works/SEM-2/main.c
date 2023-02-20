#include <stdio.h>
#include <stdlib.h>

void menu() {
    printf("What do you want to print?");
    printf("How you want ot sort?\n1)by HP\t2)by ATK\t3)by armor\t4)by name\n");
}

struct character {
    int hp, atk, armor;
    char *name;
};

void printArray(int n, struct character squad[]) {
    for (int i = 0; i < n; i++) {
        printf("Name:%s \t Hp: %d \t Atk: %d \t Armor: %d \n", squad[i].name, squad[i].hp, squad[i].atk, squad[i].armor);
    }
}

int main() {
    menu();
    struct character squad[] = {{33465, 1692, 1111, "Hu Tao"},
                                {15444, 1281, 591, "Nahida"},
                                {20867, 1347, 1089, "Raiden"},
                                {15324, 2566, 741, "Ganyu"}};
    int n = sizeof(squad) / sizeof(squad[0]);
    printArray(n, squad);
    return 0;
}
