#include "library.h"

int countWords(FILE *file) {
    char line[MaxWordLength];
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
        wordCount[i].size = wordCount[i].count * (int)strnlen_s(wordCount[i].word, sizeof(wordCount[i].word));
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
    if (maxWordCount == 0)
        exit(EXIT_FAILURE);
    //    printf("Total words in file: %d\n", maxWordCount);
    fseek(file, 0, SEEK_SET);
    wordCnt *wordCount = (wordCnt *) malloc(maxWordCount * sizeof(wordCnt));

    while (fscanf_s(file, "%100s", word) == 1) {
        int found = 0;
        int j = 0;
        size_t len = strnlen_s(word, sizeof(word));
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
            strcpy_s(wordCount[*count].word, sizeof(wordCount[*count].word), word);
            wordCount[*count].count = 1;
            (*count)++;
        }
    }
    getMemory(wordCount, *count);
    return wordCount;
}

int profit(wordCnt first, wordCnt last) {
    size_t firstLen = strnlen_s(first.word, sizeof(first.word));
    size_t lastLen = strnlen_s(last.word, sizeof(last.word));
    int prof = (int)(firstLen * first.count + lastLen * last.count - (firstLen * last.count + lastLen * first.count + 2 + lastLen + firstLen));
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
    wordCnt *dictionary = (wordCnt *) malloc(*dictCount * sizeof(wordCnt));
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
            *dictCount += 2;
            dictionary = realloc(dictionary, *dictCount * sizeof(wordCnt));
            strcpy_s(dictionary[*dictCount - 2].word, sizeof(dictionary[*dictCount - 2].word), wordCount[0].word);
            strcpy_s(dictionary[*dictCount - 1].word, sizeof(dictionary[*dictCount - 1].word), wordCount[deleteIndex].word);
            removeWord(&wordCount, deleteIndex, &count);
            removeWord(&wordCount, 0, &count);
        }
    }
    free(wordCount);
    return dictionary;
}

void swap(FILE *inFile, FILE *outFile, int dictCount, wordCnt *dictionary) {
    for (int i = 0; i < dictCount; i++) {
        fprintf(outFile, "%s ", dictionary[i].word);
    }
    fprintf(outFile, "\n");
    char word[MaxWordLength];
    fseek(inFile, 0, SEEK_SET);
    int fl;
    while (!feof(inFile)) {
        if (fscanf_s(inFile, "%[^ ,.\n\t\"?!';:`’]", word) == 1) {
            fl = 0;
            for (int i = 0; i < dictCount; i++) {
                if (strcmp(dictionary[i].word, word) == 0) {
                    if (i % 2 == 1) {
                        fprintf(outFile, "%s", dictionary[i - 1].word);
                        fl = 1;
                    } else {
                        fprintf(outFile, "%s", dictionary[i + 1].word);
                        fl = 1;
                    }
                    break;
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