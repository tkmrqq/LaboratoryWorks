//header.h

#ifndef HEADER_H
#define HEADER_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MaxWordLength 100

typedef struct WordCount_t {
    string word;
    int count;
    int size;
} wordCnt;

vector<wordCnt> countWordOccur(fstream &file, int *count);
vector<wordCnt> getDictionary(vector<wordCnt> wordCount, int count, int *dictCount);
void swap(fstream &inFile, fstream &outFile, int dictCount, vector<wordCnt> dictionary);
void printFileSize(fstream &inFile, fstream &outFile);
void removeWord(vector<wordCnt> *wordCount, int index, int *count);

void printStruct(vector<wordCnt> wordCount, int count);

#endif // HEADER_H