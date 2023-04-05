#include "library.h"

int main() {
    const char *compFileName = {"../compressed.txt"};
    const char *inFileName = {"../file.txt"};
    int count = 0;
    int dictCount = 0;
    FILE *inFile;
    fopen_s(&inFile,inFileName, "r");
    if (inFile == NULL) {
        return -1;
    }
    FILE *outFile;
    fopen_s(&outFile, compFileName, "w");
    if (outFile == NULL) {
        fclose(inFile);
        return -1;
    }

    wordCnt *words = countWordOccur(inFile, &count);
    qsort(words, count, sizeof(wordCnt), (int (*)(const void *, const void *)) compare);

    while (words[count - 1].size == 0)
        removeWord(&words, count - 1, &count);
    wordCnt *dictionary = getDictionary(words, count, &dictCount);

    swap(inFile, outFile, dictCount, dictionary);
    printFileSize(inFile, outFile);
    free(dictionary);
    fclose(inFile);
    fclose(outFile);
    return 0;
}