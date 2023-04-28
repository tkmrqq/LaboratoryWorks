#include "../files/treeLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *createNode(const char *question) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->question = (char *) malloc(strlen(question) + 1);
    strcpy(node->question, question);
    node->yes = NULL;
    node->no = NULL;
    return node;
}

void insert(Node *node, const char *question, const char *answer) {
    if (strcmp(answer, "yes") == 0) {
        if (node->yes == NULL) {
            node->yes = createNode(question);
        } else {
            insert(node->yes, question, answer);
        }
    } else if (strcmp(answer, "no") == 0) {
        if (node->no == NULL) {
            node->no = createNode(question);
        } else {
            insert(node->no, question, answer);
        }
    }
}

void play(Node *node, Node ***answers, int *answersSize) {
    if (node->yes == NULL) {
        printf("Это %s?\n", node->question);
    } else {
        printf("%s?\n", node->question);
    }
    char response[size/10];
    while (strcmp(response, "yes") != 0 && strcmp(response, "no") != 0) {
        scanf("%9s", response);
    }
    if (strcmp(response, "yes") == 0) {
        *answers = realloc(*answers, (*answersSize + 1) * sizeof(Node *));
        (*answers)[*answersSize] = node;
        (*answersSize)++;
        if (node->yes != NULL) {
            play(node->yes, answers, answersSize);
        } else {
            printf("Ура! Я угадал! /(^0^)/\n");
        }
    } else if (strcmp(response, "no") == 0) {
        if (node->no != NULL) {
            play(node->no, answers, answersSize);
        } else {
            printf("Не угадал\nЧто это было?\n");
            char newObject[size];
            char newQuestion[size];
            scanf_s("%s", newObject);
            printf("Каким вопросом можно отличить %s от %s:\n", newObject, node->question);
            scanf_s(" %[^\n]s", newQuestion);
            Node *newQuestionNode = createNode(newQuestion);
            Node *newObjectNode = createNode(newObject);
            newQuestionNode->yes = newObjectNode;
            node->no = newQuestionNode;
        }
    }
}

void saveToFile(FILE *fp, Node *node) {
    if (node == NULL) {
        return;
    }
    fprintf(fp, "{");
    fprintf(fp, "\"question\":\"%s\"", node->question);
    if (node->yes != NULL) {
        fprintf(fp, ",\"yes\":");
        saveToFile(fp, node->yes);
    }
    if (node->no != NULL) {
        fprintf(fp, ",\"no\":");
        saveToFile(fp, node->no);
    }
    fprintf(fp, "}");
}

void save(Node *root, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        saveToFile(fp, root);
        fclose(fp);
    }
}

int getEnd(const char *line) {
    int c = 0;
    int end = 0;
    for (int i = 0; i < (int) strlen(line); i++) {
        if (line[i] == '{')
            c++;
        if (line[i] == '}') {
            c--;
            if (c == 0) {
                end = i;
                break;
            }
        }
    }
    return end;
}

void parse(const char *yesStart, const char *toCheck, const char *line, Node **node) {
    if (yesStart != NULL && strcmp(toCheck, "yes") == 0) {
        int end = getEnd(yesStart);
        char *yesEnd = calloc(end - 5, sizeof(char));
        strncpy(yesEnd, yesStart + 6, end - 5);
        if (yesEnd != NULL) {
            (*node)->yes = parseNode(yesEnd);
            free(yesEnd);
        }
        char *afterYes = calloc(strlen(line) - end - 2, sizeof(char));
        strncpy(afterYes, yesStart + end + 2, strlen(line) - end - 2);
        const char *noStart = strstr(afterYes, "\"no\":{");
        if (noStart != NULL) {
            end = getEnd(noStart);
            char *noEnd = calloc(end - 5, sizeof(char));
            strncpy(noEnd, noStart + 5, end - 4);
            if (noEnd != NULL) {
                (*node)->no = parseNode(noEnd);
                free(noEnd);
            }
        }
    } else {
        const char *noStart = strstr(line, "\"no\":{");
        if (noStart != NULL) {
            int end = getEnd(noStart);
            char *noEnd = calloc(end - 5, sizeof(char));
            strncpy(noEnd, noStart + 5, end - 5);
            if (noEnd != NULL) {
                (*node)->no = parseNode(noEnd);
                free(noEnd);
            }
        }
    }
}

Node *parseNode(const char *line) {
    const char *qStart = strstr(line, "\":\"");
    if (qStart == NULL) {
        return NULL;
    }
    qStart += 3;
    const char *qEnd = strchr(qStart, '\"');
    if (qEnd == NULL) {
        return NULL;
    }

    char *question = (char *) malloc((qEnd - qStart + 1) * sizeof(char));
    memcpy(question, qStart, qEnd - qStart);
    question[qEnd - qStart] = '\0';

    Node *node = createNode(question);
    free(question);
    const char *yesStart = strstr(line, "\"yes\":{");

    char *tocheck = (char *) malloc(4 * sizeof(char));
    memcpy(tocheck, qEnd + 3, 3);
    tocheck[3] = '\0';

    parse(yesStart, tocheck, line, &node);
    free(tocheck);
    return node;
}

Node *loadFromFile(FILE *fp) {
    int line_length = 0;
    char *line = (char *) malloc(sizeof(char));
    char c;
    while ((c = fgetc(fp)) != '\n' && c != EOF) {
        line[line_length] = c;
        line_length++;
        line = (char *) realloc(line, (line_length + 1) * sizeof(char));
    }
    line[line_length] = '\0';
    if (c == EOF && line_length == 0) {
        return NULL;
    }
    Node *node = parseNode(line);
    free(line);
    return node;
}

Node *load(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error! File not found\n");
        return NULL;
    }
    Node *root = loadFromFile(fp);
    fclose(fp);
    return root;
}

void clearMemory(Node *node) {
    if (node->question != NULL)
        free(node->question);
    if (node->yes != NULL) {
        clearMemory(node->yes);
    }
    if (node->no != NULL) {
        clearMemory(node->no);
    }
    free(node);
}

void printTree(struct Node* root, int level, Node** answers, int answersLen) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    int founded = 0;
    for(int i = 0; i < answersLen; i++) {
        if(answers[i] == root) {
            founded = 1;
            break;
        }
    }
    if(founded)
        printf("\033[32m= %s\033[0m\n", root->question);
    else
        printf("\033[31m- %s\033[0m\n", root->question);

    printTree(root->yes, level+1, answers, answersLen);
    printTree(root->no, level, answers, answersLen);
}



