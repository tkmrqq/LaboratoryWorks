#include <stdio.h>
#include <stdlib.h>

void readFile(FILE* file, FILE* file2, int k){
    char word[100];
    int fl=1;
    while(fgets(word, sizeof(word), file) != NULL){
        if(fl >= k && fl < k+5){
            fputs(word, file2);
        }
        fl++;
    }
}

int main(){
    FILE* file1 = fopen("../test1.txt", "r");
    FILE* file2 = fopen("../test2.txt", "w");
    readFile(file1, file2, 3);
}



//Есть файл с 10+ строками
//из него переписать во второй файл строки начинаю с k до k+5;