#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxWordLength 100

typedef struct WordCount_t {
    char *word;
    int count;
    int size;
} wordCnt;

int countWords(FILE *file);
int isLetter(char Ch);
char toLower(char Ch);
size_t compare(const wordCnt *a, const wordCnt *b);
void getMemory(wordCnt *wordCount, int count);
void printStruct(wordCnt *wordCount, int count);
wordCnt *countWordOccur(FILE *file, int *count);
int profit(wordCnt first, wordCnt last);
wordCnt *getDictionary(wordCnt *wordCount, int count, int *dictCount);
void swap(FILE *inFile, FILE *outFile, int dictCount, wordCnt *DictCount);
void printFileSize(FILE *inFile, FILE *outFile);
void removeWord(wordCnt **wordCount,int index, int *count);
