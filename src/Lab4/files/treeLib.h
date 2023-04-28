#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define path "C:/GitHub/Laboratory-works/src/Lab4/db.txt"

#define Size 1024

typedef struct Node_t {

    char *data;
    struct Node_t *right;
    struct Node_t *left;
} Node;

void functions(int *x);
void getMenuIndex(int *x);
void freeTree(Node * Tree);
void makeNewDataBase(char *Quest, char *Word, Node *Tree, FILE *Data, char *GetAnswer);
void getQuestion(char *Quest);
void addNewElementInDataBase(char *Word, Node *tree, FILE *Data, char *getAnswer);
int getAns();
void checkAnswer(char *Word, Node *Tree, FILE *Data, char *getAnswer);
void getWord(char *Word);
void treePrint(Node *Tree, char **getAnswer);
Node * createFromData(Node *Tree, FILE *Data);