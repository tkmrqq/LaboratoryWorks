#include "library.h"

int countWords(FILE *file) {
    char line[1000];
    const char *word;
    int count = 0;
    char *saveptr;
    while (fgets(line, sizeof(line), file) != NULL) {
        word = strtok_r(line, " \t\n", &saveptr);
        while (word != NULL) {
            count++;
            word = strtok_r(NULL, " \t\n", &saveptr);
        }
    }
    return count;
}

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

size_t compare(const wordCnt *a, const wordCnt *b) {
    return b->size - a->size;
}

void getMemory(wordCnt *wordCount, int count) {
    for (int i = 0; i < count; i++) {
        wordCount[i].size = wordCount[i].count * (int) strlen(wordCount[i].word);
    }
}

void printStruct(wordCnt *wordCount, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s: %d\t[%d]\n", wordCount[i].word, wordCount[i].count, wordCount[i].size);
    }
}

wordCnt *countWordOccur(FILE *file, int *count) {
    char word[MaxWordLength];
    *count = 0;
    int maxWordCount = countWords(file);
    //    printf("Total words in file: %d\n", maxWordCount);
    fseek(file, 0, SEEK_SET);
    wordCnt *wordCount = (wordCnt *) malloc(maxWordCount * sizeof(wordCnt));
    while (fscanf(file, "%s", word) == 1) {
        int found = 0;
        int j = 0;
        size_t len = strlen(word);
        for (int i = 0; i < len; i++) {
            if (isLetter(word[i])) {
                word[j++] = word[i];
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
    }
    getMemory(wordCount, *count);
    return wordCount;
}

int profit(wordCnt first, wordCnt last) {
    size_t firstLen = strlen(first.word);
    size_t lastLen = strlen(last.word);
    int prof = firstLen * first.count + lastLen * last.count - (firstLen * last.count + lastLen * first.count + 2 + lastLen + firstLen);
    return prof;
}

void removeWord(wordCnt **wordCount, int index, int *count) {
    for (int i = index; i < *count - 1; i++) {
        (*wordCount)[i] = (*wordCount)[i + 1];
    }
    *wordCount = realloc(*wordCount, (*count - 1) * sizeof(wordCnt));
    (*count)--;
}

wordCnt *getDictionary(wordCnt *wordCount, int count, int *dictCount) {
    int maxProfit = 1;
    int sum = -2;
    wordCnt *DictCount = (wordCnt *) malloc(*dictCount * sizeof(wordCnt));
    while (maxProfit > 0) {
        maxProfit = INT_MIN;
        int deleteIndex;
        int j;
        for (int i = count - 1; i > 0; i--) {
            if ((j = profit(wordCount[0], wordCount[i])) > maxProfit) {
                maxProfit = j;
                deleteIndex = i;
            }
        }
        if (maxProfit > 0) {
            //sum += maxProfit;
            *dictCount += 2;
            DictCount = realloc(DictCount, *dictCount * sizeof(wordCnt));
            strcpy(DictCount[*dictCount - 2].word, wordCount[0].word);
            strcpy(DictCount[*dictCount - 1].word, wordCount[deleteIndex].word);
            removeWord(&wordCount, deleteIndex, &count);
            removeWord(&wordCount, 0, &count);
        }
    }
    free(wordCount);
    return DictCount;
}

void swap(FILE *inFile, FILE *outFile, int dictCount, wordCnt *DictCount) {
    for (int i = 0; i < dictCount; i++) {
        fprintf(outFile, "%s ", DictCount[i].word);
    }
    fprintf(outFile, "\n");
    char word[MaxWordLength];
    fseek(inFile, 0, SEEK_SET);
    int fl;
    while (!feof(inFile)) {
        if (fscanf(inFile, "%[^ ,.\n\t\"?!';:`’]", word) == 1) {
            fl = 0;
            for (int i = 0; i < dictCount; i++) {
                if (strcmp(DictCount[i].word, word) == 0) {
                    if (i % 2 == 1) {
                        fprintf(outFile, "%s", DictCount[i - 1].word);
                        fl = 1;
                        break;
                    } else {
                        fprintf(outFile, "%s", DictCount[i + 1].word);
                        fl = 1;
                        break;
                    }
                }
            }
            if (fl == 1) continue;
            fprintf(outFile, "%s", word);
        } else {
            char ch = (char) fgetc(inFile);
            if (feof(inFile))
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
    printf("Difference is %ld bytes\n", (inSize - outSize));
    printf("Difference is %ld KB\n", (inSize - outSize) / 1024);
}