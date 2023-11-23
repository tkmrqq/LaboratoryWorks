#include "header.h"

int countWords(fstream& file) {
    char line[MaxWordLength];
    const char *word;
    int count = 0;
    char *context;
    while (file >> line){
        word = strtok_s(line, " \t\n", &context);
        while (word != nullptr) {
            count++;
            word = strtok_s(nullptr, " \t\n", &context);
        }
    }
    return count;
}

int isLetter(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;
    return 0;
}

size_t compare(const wordCnt *a, const wordCnt *b) {
    return b->size - a->size;
}

void getMemory(vector<wordCnt> wordCount, int count) {
    for (int i = 0; i < count; i++) {
        wordCount[i].size = wordCount[i].count * (int) strnlen_s(wordCount[i].word.c_str(), wordCount[i].word.size());
    }
}

void printStruct(vector<wordCnt> wordCount, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s: %d\t[%d]\n", wordCount[i].word.c_str(), wordCount[i].count, wordCount[i].size);
    }
}

vector<wordCnt> countWordOccur(fstream& file, int *count) {
    string word;
    *count = 0;
    int maxWordCount = countWords(file);

    if (maxWordCount == 0)
        exit(EXIT_FAILURE);

    file.seekg(0, ios::beg);

    vector<wordCnt> wordCount(maxWordCount);
//    wordCnt *wordCount = (wordCnt *) malloc(maxWordCount * sizeof(wordCnt));

    while(file >> word){
        int found = 0;
        int j = 0;
        size_t len = word.length();
        for (int i = 0; i < len; i++) {
            if (isLetter(word[i])) {
                word[j++] = word[i];
            }
        }
        word[j] = '\0';
        for (int i = 0; i < *count; i++) {
            if (wordCount[i].word == word) {
                wordCount[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            wordCount[*count].word = word;
            wordCount[*count].count = 1;
            (*count)++;
        }
    }

    getMemory(wordCount, *count);
    return wordCount;
}

int profit(const wordCnt& first, const wordCnt& last) {
    size_t firstLen = first.word.length();
    size_t lastLen = last.word.length();
    int prof = (int) (firstLen * first.count + lastLen * last.count - (firstLen * last.count + lastLen * first.count + 2 + lastLen + firstLen));
    return prof;
}

void removeWord(vector<wordCnt> *wordCount, int index, int *count) {
    for (int i = index; i < *count - 1; i++) {
        (*wordCount)[i] = (*wordCount)[i + 1];
    }
    if (*count - 1 == 0)
        exit(EXIT_FAILURE);
//    *wordCount = realloc(*wordCount, (*count - 1) * sizeof(wordCnt));
    wordCount->resize(*count - 1);
    (*count)--;
}

vector<wordCnt> getDictionary(vector<wordCnt> wordCount, int count, int *dictCount) {
    int maxProfit = 1;
//    wordCnt *dictionary = (wordCnt *) malloc(*dictCount * sizeof(wordCnt));
    vector<wordCnt> dictionary(*dictCount);

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
            dictionary.resize(*dictCount);
            dictionary[*dictCount - 2].word = wordCount[0].word;
            dictionary[*dictCount - 1].word = wordCount[deleteIndex].word;
/*            strcpy_s(dictionary[*dictCount - 2].word, sizeof(dictionary[*dictCount - 2].word), wordCount[0].word);
            strcpy_s(dictionary[*dictCount - 1].word, sizeof(dictionary[*dictCount - 1].word), wordCount[deleteIndex].word);*/
            removeWord(&wordCount, deleteIndex, &count);
            removeWord(&wordCount, 0, &count);
        }
    }
//    free(wordCount);
    wordCount.clear();
    return dictionary;
}

void swap(fstream& inFile, fstream& outFile, int dictCount, vector<wordCnt> dictionary) {
    for (int i = 0; i < dictCount; i++) {
        outFile << dictionary[i].word << ' ';
    }
    outFile << "\n";
    string word;
    inFile.seekg(0, ios::beg);
    int fl;
    while (inFile >> word) {
        fl = 0;
        for (int i = 0; i < dictCount; i++) {
            if (dictionary[i].word == word) {
                if (i % 2 == 1) {
                    outFile << dictionary[i - 1].word;
                    fl = 1;
                } else {
                    outFile << dictionary[i + 1].word;
                    fl = 1;
                }
                break;
            }
        }
        if (fl == 1) continue;
        outFile << word;
    }
}

void printFileSize(fstream& inFile, fstream& outFile) {
    inFile.seekg(0, std::ios::end);
    long inSize = inFile.tellg();
    outFile.seekg(0, std::ios::end);
    long outSize = outFile.tellg();
    std::cout << "Original file size is " << inSize << " bytes" << std::endl;
    std::cout << "Compressed file size is " << outSize << " bytes" << std::endl;
    std::cout << "Difference is " << (inSize - outSize) << " bytes" << std::endl;
    std::cout << "Difference is " << (inSize - outSize) / 1024 << " KB" << std::endl;
}