#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word_t {
    char word[100];
    int length;
} Word;

void printStruct(Word *words, int wordsCount) {
    printf("Count = %d\n", wordsCount);
    for (int i = 0; i < wordsCount; ++i) {
        printf("Length = %d; Word = %s", words[i].length, words[i].word);
    }
}

int wordCount(FILE *file) {
    char line[100];
    const char *word;
    int count = 0;
    char *context;
    while (fgets(line, sizeof(line), file) != NULL) {
        word = strtok_s(line, " \t\n", &context);
        while (word != NULL) {
            count++;
            word = strtok_s(NULL, " \t\n", &context);
        }
    }
    return count;
}

void addWord(Word *words, const char *word, int length, int i) {
    words[i].length = length;
    strcpy(words[i].word, word);
}

void swap(Word *a, Word *b) {
    Word tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion_sort(Word* words, int wordsCount) {
    for (int k = 1; k < wordsCount; k++)
        for (int i = k; i > 0 && words[i - 1].length < words[i].length; i--)
            swap(&words[i], &words[i - 1]);
}

void writeFile(Word* words, int wordsCount){
    FILE* file = fopen("../file2.txt", "w");
    for (int i = 0; i < wordsCount; ++i) {
        fprintf(file, "%s", words[i].word);
    }
    fclose(file);
}

int main() {
    FILE *fp = fopen("../file.txt", "r");
    char word[100];
    int wordsCount = wordCount(fp);
    Word *words = (Word *) malloc(wordsCount * sizeof(Word));
//    words->word = (char *) malloc(255 * sizeof(char));
    int i = 0;
    fseek(fp, 0, SEEK_SET);
    while (fgets(word, sizeof(word), fp) != NULL) {
        size_t len = strlen(word);
        addWord(words, word, len, i);
        i++;
    }
    printStruct(words, wordsCount);
    fclose(fp);
    insertion_sort(words, wordsCount);
    writeFile(words, wordsCount);
}