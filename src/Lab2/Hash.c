#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10000
#define MAX_WORD_SIZE 100

typedef struct Node {
    char *word;
    int count;
    struct Node *next;
} Node;

int hash(char *word) {
    int hash = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hash += word[i];
    }
    return hash % TABLE_SIZE;
}

void add_word(Node **table, char *word) {
    int index = hash(word);
    Node *node = table[index];
    while (node != NULL) {
        if (strcmp(node->word, word) == 0) {
            node->count++;
            return;
        }
        node = node->next;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = (char *)malloc(strlen(word) + 1);
    strcpy(new_node->word, word);
    new_node->count = 1;
    new_node->next = table[index];
    table[index] = new_node;
}

void print_table(Node **table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = table[i];
        while (node != NULL) {
            printf("%s: %d\n", node->word, node->count);
            node = node->next;
        }
    }
}

int main() {
    FILE *file = fopen("../file.txt", "r");
    if (file == NULL) {
        printf("Failed to open file!\n");
        return 1;
    }
    Node *table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }
    char word[MAX_WORD_SIZE];
    while (fscanf(file, "%s", word) == 1) {
        // приводим слово к нижнему регистру
        for (int i = 0; word[i] != '\0'; i++) {
            word[i] = tolower(word[i]);
        }
        add_word(table, word);
    }
    fclose(file);
    print_table(table);
    return 0;
}
