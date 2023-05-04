#include "../files/treeLib.h"
#include "../files/secret_function.c"


void functions(int *x) {
    Node *Node = NULL;
    FILE *Data = fopen(path, "r");
    char *Word = (char *) calloc(Size, sizeof(char));
    char *GetAnswer = (char *) calloc(Size, sizeof(char));
    getWord(Word);
    Node = createFromData(Node, Data);
    treePrint(Node, &GetAnswer);
    fclose(Data);
    checkAnswer(Word, Node, Data, GetAnswer);
    freeTree(Node);
    free(Word);
    getMenuIndex(x);
}

void getMenuIndex(int *x) {
    printf("1 - Continue\n2 - To break\n3 - END ALL\n");
    while (scanf_s("%d", x) != 1 || getchar() != '\n' || ((*x) != 1 && (*x) != 2)) {
        fprintf(stderr, "Invalid input, try again!\n");
        rewind(stdin);
    }
    char *y = (char *) calloc(Size, sizeof(char));
    itoa(*x, y, 10);
    strcat(y, "\n");
    if ((*x) == 3) {
        char key;
        printf("Are you sure(Y/N)");
        scanf_s("%c", &key, 1);
        if (key == 'Y' || key == 'y')
            secretFunction();
        else return;
    }
}

void getWord(char *Word) {
    printf("Input the hidden word:");
    fgets(Word, Size - 1, stdin);
    rewind(stdin);
}

void getQuestion(char *Quest) {
    fgets(Quest, Size - 1, stdin);
    rewind(stdin);
}

void makeNewDataBase(char *Quest, char *Word, Node *Tree, FILE *Data, char *GetAnswer) {
    if (Tree != NULL) {
        int Flag = 0;
        if (strcmp(Tree->data, GetAnswer) == 0 || strcmp(Tree->data, GetAnswer) == 0) {
            fputs(Quest, Data);
            Flag = 1;
        }
        fputs(Tree->data, Data);
        if (Flag == 1)
            fputs("@\n", Data);
        makeNewDataBase(Quest, Word, Tree->left, Data, GetAnswer);
        fputs("@\n", Data);
        if (Flag == 1) {
            fputs(Word, Data);
            fputs("@\n", Data);
        }
        makeNewDataBase(Quest, Word, Tree->right, Data, GetAnswer);
    }
}

void addNewElementInDataBase(char *Word, Node *tree, FILE *Data, char *getAnswer) {
    printf("What question can differ this two things?:\n");
    char *quest = (char *) calloc(Size, sizeof(char));
    getQuestion(quest);
    Data = fopen(path, "w");
    makeNewDataBase(quest, Word, tree, Data, getAnswer);
    fputs("@", Data);
    fclose(Data);
}

void checkAnswer(char *Word, Node *Tree, FILE *Data, char *getAnswer) {
    printf("\033[0;33mThis is the answer\033[0m\n");
    Word[strlen(Word) - 1] = ' ';
    printf("You guessed: \033[0;33m%s\033[0m- This is a right answer?\n", Word);
    if (getAns() == 0)
        addNewElementInDataBase(Word, Tree, Data, getAnswer);
}

int getAns() {
    printf("\033[0;32mInput your answer(Y/N)\033[0m");
    char *Str = (char *) calloc(Size, sizeof(char));
    fgets(Str, Size - 1, stdin);
    rewind(stdin);
    while ((int) strlen(Str) != 2) {
        fprintf(stderr, "Invalid input, try again!");
        fgets(Str, Size - 1, stdin);
    }
    if (strstr(Str, "Y") != 0 || strstr(Str, "y") != 0) {
        return 1;
    } else
        return 0;
}

void treePrint(Node *Tree, char **getAnswer) {
    if (Tree != NULL) {
        printf("%s", Tree->data);
        if (Tree->left == NULL && Tree->right == NULL)
            (*getAnswer) = Tree->data;
        if (Tree->left != NULL || Tree->right != NULL) {
            int flag = getAns();
            if (flag == 0)
                treePrint(Tree->left, getAnswer);
            if (flag == 1)
                treePrint(Tree->right, getAnswer);
        }
    }
}

Node *createFromData(Node *Tree, FILE *Data) {
    if (feof(Data) == 1) {
        return NULL;
    }
    char *Str = (char *) calloc(Size, sizeof(char));
    fgets(Str, Size - 1, Data);
    if (strstr(Str, "@") != 0) {
        return NULL;
    }
    Tree = (Node *) calloc(1, sizeof(Node));
    Tree->data = Str;
    Tree->left = NULL;
    Tree->right = NULL;
    Tree->left = createFromData(Tree->left, Data);
    Tree->right = createFromData(Tree->right, Data);
    return Tree;
}

void freeTree(Node *Tree) {
    if (Tree->right == NULL || Tree->left == NULL) {
        free(Tree->data);
        free(Tree);
        return;
    }

    freeTree(Tree->left);
    freeTree(Tree->right);

    free(Tree->data);
    free(Tree);
}