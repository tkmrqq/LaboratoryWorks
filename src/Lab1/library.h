#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {CRYO, PYRO, ELECTRO, DENDRO} Element;

typedef struct character_t {
    int hp;
    int atk;
    int armor;
    char *name;
    Element element;
} character;

character * initArr(int size);
char* get_string();
int createArray(character characters[]);
int additionalSize();
char toLower(char in);
void printCharacter(character c[], int n);
int compareByHp(const character *a, const character *b);
int compareByAtk(const character *a, const character *b);
int compareByArmor(const character *a, const character *b);
int compareByName(const character *a, const character *b);
int compareByElement(const character *a, const character *b);
char *getSortField();
int chooseSort();
void sortCharacters(character characters[], int numChars);
void Remove(character characters[], int *len);
void menu(character characters[], int n);


