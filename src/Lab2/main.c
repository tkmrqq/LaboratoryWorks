#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxWordLength 100

typedef struct WordCount {
    char word[MaxWordLength];
    int count;
    int size;
} wordCnt;

int isLetter(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;
    return 0;
}

char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return (char) (ch - ('Z' - 'z'));
    return ch;
}

int isLongWord(char *word) {
    return strlen(word) >= 7;
}

int isShortWord(char *word) {
    return strlen(word) <= 2;
}

void printStruct(wordCnt *wordCount, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s: %d\t[%d]\n", wordCount[i].word, wordCount[i].count, wordCount[i].size);
    }
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

wordCnt *countWordOccur(FILE *file, int *count) {
    char word[MaxWordLength];
    *count = 0;
    int maxWordCount = countWords(file);
    printf("Total words in file: %d\n", maxWordCount);
    fseek(file, 0, SEEK_SET);
    wordCnt *wordCount = (wordCnt *) malloc(maxWordCount * sizeof(wordCnt));
    while (fgets(word, MaxWordLength, file)) {
        char *token = strtok(word, " \t\n");
        while (token) {
            int found = 0;
            int j = 0;
            size_t len = strlen(word);
            for (int i = 0; i < len; i++) {
                if (isLetter(word[i])) {
                    word[j++] = toLower(word[i]);
                }
            }
            word[j] = '\0';
            for (int i = 0; i < *count; i++) {
                if (strcmp(wordCount[i].word, word) == 0) {
                    wordCount[i].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(wordCount[*count].word, word);
                wordCount[*count].count = 1;
                (*count)++;
            }
            token = strtok(NULL, "\t\n");
        }
    }
    for (int i = 0; i < *count; i++) {
        wordCount[i].size = wordCount[i].count * strlen(wordCount[i].word);
    }
    return wordCount;
}

int findMostPopularLongWord(wordCnt *wordCount, int count) {
    int maxCount = 0;
    int maxIndex = 0;
    for (int i = 0; i < count; ++i) {
        if (wordCount[i].count > maxCount && isLongWord(wordCount[i].word)) {
            maxCount = wordCount[i].count;
            maxIndex = i;
        }
    }
    return maxIndex;
}

int findMostUnpopularWord(wordCnt *wordCount, int count) {
    int minCount = INT_MAX;
    int minIndex = 0;
    for (int i = 0; i < count; ++i) {
        if (wordCount[i].count < minCount && isShortWord(wordCount[i].word)) {
            minCount = wordCount[i].count;
            minIndex = i;
        }
    }
    return minIndex;
}

size_t compare(const struct WordCount *a, const struct WordCount *b) {
    return (b->size) - (a->size);
}

void removeWord(wordCnt **wordCount,int index, int *count) {
    if (index < 0 || index >= *count) {
        printf("Invalid index\n");
        return;
    }
    for (int i = index; i < *count - 1; i++) {
        (*wordCount)[i] = (*wordCount)[i + 1];
    }
    *wordCount = realloc(*wordCount, (*count - 1) * sizeof(wordCnt));
    (*count)--;
}

void replaceWords(wordCnt *wordCount, char *input_file_name, char *output_file_name, int aIndex, int bIndex) {
    FILE *input_file = fopen(input_file_name, "r");
    FILE *output_file = fopen(output_file_name, "w");
    char line[MaxWordLength];
    char *word;
    int index = 0;

    while (fgets(line, MaxWordLength, input_file) != NULL) {
        word = strtok(line, " \t\n");

        while (word != NULL) {
            if (index == aIndex) {
                fprintf(output_file, "%s ", wordCount[bIndex].word);
            } else if (index == bIndex) {
                fprintf(output_file, "%s ", wordCount[aIndex].word);
            } else {
                fprintf(output_file, "%s ", word);
            }
            word = strtok(NULL, " \t\n");
            index++;
        }
        fprintf(output_file, "\n");
    }

    fclose(input_file);
    fclose(output_file);
}

int main() {
    int count;
    FILE *inFile = fopen("../file.txt", "r");
    if (inFile == NULL) {
        fprintf(stderr, "Failed to open file!");
        return -1;
    }

    FILE *outFile = fopen("../file.txt", "r");
    if (outFile == NULL) {
        fprintf(stderr, "Failed to open file!");
        return -1;
    }

    wordCnt *wordCount = countWordOccur(inFile, &count);
    qsort(wordCount, count, sizeof(wordCnt), (int (*)(const void *, const void *)) compare);
//    printStruct(wordCount, count);
    int aIndex = findMostPopularLongWord(wordCount, count);
    int bIndex = findMostUnpopularWord(wordCount, count);
    char *popWord = wordCount[aIndex].word;
    char *unpopWord = wordCount[bIndex].word;
    printf("Long pop word: %s\n", popWord);
    printf("Short unpop word: %s\n", unpopWord);
    while(1){
        replaceWords(*wordCount, inFile, outFile, aIndex, bIndex)
    }
    free(wordCount);
    fclose(file);
    return 0;
}
/*
int main() {
    char inFileName[] = "../file.txt";
    char outFileName[] = "../out.txt";
    int popularWord;
    int unpopularWord;

    FILE *inFile = fopen(inFileName, "r");
    if (inFile == NULL) {
        fprintf(stderr, "Failed to open file!");
        return -1;
    }
    FILE *outFile = fopen(outFileName, "w+");
    if (outFile == NULL) {
        printf("Error: Could not open output file.\n");
        return -1;
    }
    int count;
    wordCnt *wordCount = countWordOccur(inFile, &count);
    qsort(wordCount, count, sizeof(wordCnt), (int (*)(const void *, const void *)) compare);
    fseek(inFile, 0, SEEK_SET);
    int i = 0;
    char **words = NULL;
    */
/*    while (1) {
        popularWord = findMostPopularLongWord(wordCount, count);
        unpopularWord = findMostUnpopularWord(wordCount, count);
        replaceWords(wordCount, inFileName, outFileName, popularWord, unpopularWord);
        removeWord(&wordCount, &count, popularWord);
        removeWord(&wordCount, &count, unpopularWord);
        i++;
        if (i == 10)
            break;
        printf("1)%s\t2)%s\n", wordCount[popularWord].word, wordCount[unpopularWord].word);
    }*//*

    while(1) {
        int longWordPos = findMostPopularLongWord(wordCount, count);
        if(longWordPos == -1)
            break;
        int shortWordPos = findMostUnpopularWord(wordCount, count);
        if(shortWordPos == -1)
        {
            removeWord(&wordCount, longWordPos, &count);
            continue;
        }
        fprintf(outFile, "%s", wordCount[shortWordPos].word);
        fprintf(outFile, "%c", ' ');
        fprintf(outFile, "%s", wordCount[longWordPos].word);
        fprintf(outFile, "%c", ' ');
        for(int i = 0; i < count; i++) {
            if(strcmp(words[i], wordCount[shortWordPos].word) == 0)
            {
                words[i] = wordCount[longWordPos].word;
            }
            else if(strcmp(words[i], wordCount[longWordPos].word) == 0) {
                words[i] = wordCount[shortWordPos].word;
            }
        }


        removeWord(&wordCount,shortWordPos,&count);
        if(longWordPos > shortWordPos)
            removeWord(&wordCount, longWordPos-1, &count);
        else
            removeWord(&wordCount, longWordPos, &count);
    }
*/
/*    fprintf(outFile, "\n");
    for (int i = 0; i < words_size; i++) {
        if(i == words_size-1)
            fprintf(outFile, "%s", words[i]);
        else
            fprintf(outFile, "%s ", words[i]);
    }*//*

    fclose(outFile);
    return 0;
}*/
