#include "library.h"

int main() {
    char *compFileName = {"../compressed.txt"};
    int count = 0, dictCount = 0;
    FILE *inFile = fopen("../file.txt", "r");
    if (inFile == NULL) {
        return -1;
    }
    FILE *outFile = fopen(compFileName, "w");
    if (outFile == NULL) {
        return -1;
    }
    wordCnt *wordCount = countWordOccur(inFile, &count);
    qsort(wordCount, count, sizeof(wordCnt), (int (*)(const void *, const void *)) compare);
    while (wordCount[count - 1].size == 0)
        removeWord(&wordCount, count - 1, &count);
    wordCnt *DictCount = getDictionary(wordCount, count, &dictCount);
    swap(inFile, outFile, dictCount, DictCount);
    printFileSize(inFile, outFile);
    free(wordCount);
    free(DictCount);
    fclose(inFile);
    fclose(outFile);
    return 0;
}