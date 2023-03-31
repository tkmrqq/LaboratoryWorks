#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxWordLength 100

typedef struct Words {
    char word[MaxWordLength];
} words;

int isLetter(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;
    return 0;
}

int countWords(FILE *file) {
    char line[1000];
    char *word;
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        word = strtok(line, " \t\n");
        while (word != NULL) {
            count++;
            word = strtok(NULL, " \t\n");
        }
    }
    return count;
}

void printStruct(words *wordCount, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s\n", wordCount[i].word);
    }
}

words *countWordOccur(FILE *file, int *count) {
    char word[MaxWordLength];
    *count = 0;
    int maxWordCount = countWords(file);
    fseek(file, 0, SEEK_SET);
    words *wordList = (words *) malloc(maxWordCount * sizeof(words));
    int fl = 1;
    while (fl) {
        if (fscanf(file, "%[^ \n]", word) == 1) {
            int j = 0;
            size_t len = strlen(word);
            for (int i = 0; i < len; i++) {
                if (isLetter(word[i])) {
                    word[j++] = word[i];
                }
            }
            word[j] = '\0';
            strcpy(wordList[*count].word, word);
            (*count)++;
        }
        else{
            char ch = fgetc(file);
            if (ch ==  '\n') break;
        }
    }
    return wordList;
}

void swap(FILE *inFile, FILE *outFile, int count, words *wordList) {
    char word[MaxWordLength];
    int fl;
    while (!feof(inFile)) {
        if (fscanf(inFile, "%[^ ,.\n\t\"?!';:`’]", word) == 1) {
            fl = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(wordList[i].word, word) == 0) {
                    if (i % 2 == 1) {
                        fprintf(outFile, "%s", wordList[i - 1].word);
                        fl = 1;
                        break;
                    } else {
                        fprintf(outFile, "%s", wordList[i + 1].word);
                        fl = 1;
                        break;
                    }
                }
            }
            if (fl == 1) continue;
            fprintf(outFile, "%s", word);
        } else {
            char ch = (char)fgetc(inFile);
            if(feof(inFile))
                break;
            fputc(ch, outFile);
        }
    }
}

void printFileSize(FILE *inFile, FILE *outFile) {
    fseek(inFile, 0, SEEK_END);
    long inSize = ftell(inFile);
    fseek(outFile, 0, SEEK_END);
    long outSize = ftell(outFile);
    printf("Original file size is %ld bytes\n", inSize);
    printf("Compressed file size is %ld bytes\n", outSize);
    printf("Difference is %ld\n", (inSize - outSize));

}

int main(){
    int count = 0;
    FILE *compressed = fopen("../compressed.txt", "r");
    FILE *decompressed = fopen("../decompressed.txt", "w");
    words *wordList = countWordOccur(compressed, &count);
//    printStruct(wordList, count);
    swap(compressed, decompressed, count, wordList);
    printFileSize(compressed, decompressed);
    fclose(compressed);
    fclose(decompressed);
}