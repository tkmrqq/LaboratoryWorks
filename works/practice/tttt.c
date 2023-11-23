#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isVowel(char c) {
    switch (tolower(c)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return 1;
        default:
            return 0;
    }
}

size_t get_count(const char *s) {
    int count = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (isVowel(s[i])) {
            count++;
        }
    }
    return count;
}

int main() {
    printf("%zu", get_count("aeiou"));
}