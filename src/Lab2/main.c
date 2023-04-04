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

    wordCnt *wordCount = countWordOccur(inFile, &count);
    qsort(wordCount, count, sizeof(wordCnt), (int (*)(const void *, const void *)) compare);

    while (wordCount[count - 1].size == 0)
        removeWord(&wordCount, count - 1, &count);
    wordCnt *DictCount = getDictionary(wordCount, count, &dictCount);

    swap(inFile, outFile, dictCount, DictCount);
    printFileSize(inFile, outFile);
    free(DictCount);
    fclose(inFile);
    fclose(outFile);
    return 0;
}