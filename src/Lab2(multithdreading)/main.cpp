#include "header.h"

int main() {
    const char *compFileName = {"../compressed.txt"};
    const char *inFileName = {"../file.txt"};
    int count = 0;
    int dictCount = 0;
    fstream inFile(inFileName, ios::in);
    if(!inFile.is_open()){
        cout << "Unable to open file!" << endl;
        return -1;
    }

    fstream outFile (compFileName, ios::out);

    if(!outFile.is_open()){
        cout << "Unable to open file!" << endl;
        return -1;
    }


    vector<wordCnt> words = countWordOccur(inFile, &count);
//    qsort(words, count, sizeof(wordCnt), (int (*)(const void *, const void *)) compare);
    for (int i = 0; i < count; ++i) {
        cout << words[i].word;
    }

    while (words[count - 1].size == 0)
        removeWord(&words, count - 1, &count);

    vector<wordCnt> dictionary = getDictionary(words, count, &dictCount);

    printStruct(words, count);


    swap(inFile, outFile, dictCount, dictionary);
    printFileSize(inFile, outFile);
    dictionary.clear();
    inFile.close();
    outFile.close();
    return 0;
}