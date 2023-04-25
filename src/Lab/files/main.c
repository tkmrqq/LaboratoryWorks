#include "secret_function.c"
#include "treeLib.h"
#include <stdio.h>
#include <stdlib.h>

int check(int key) {
    while (!scanf_s("%d", &key) || key < 0 || key > 5) {
        fprintf(stderr, "Invalid input!\n");
        rewind(stdin);
    }
    return key;
}

int menu(int key) {
    char path[size];
    Node *tree = NULL;
    Node **answers = malloc(sizeof(Node *));
    int answersSize = 0;
    while (1) {
        printf("\nMenu:\n1) Start\n2) Load DB\n3) Save DB\n4) Exit\n");
        key = check(key);
        switch (key) {
            case 1:
                if (tree != NULL)
                    play(tree, &answers, &answersSize);
                else
                    exit(69);
                break;
            case 2:
                printf("Input DB:");
                scanf_s("%99s", path);
                tree = load(path);
                break;
            case 3:
                printf("Output DB:");
                scanf_s("%99s", path);
//                save(path, tree);
                break;
            case 0:
                printf("Bye-Bye!\n");
                //secretFunction();
            default:
                if (tree != NULL) {
//                    clearMemory(tree);
                }
                free(answers);
                exit(EXIT_SUCCESS);
        }
    }
}

int main() {
    system("chcp 65001");
    menu(0);
}
