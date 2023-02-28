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

int check();
char *inputString();
character * initArr(int size);
void createCharacter(character *characters, int numCharacters, int j);
void addStructure(character **characters, int *size);
void initSize(int *size);
char toLower(char in);
void printCharacter(character *c, int size);
int compareByHp(const character *a, const character *b);
int compareByAtk(const character *a, const character *b);
int compareByArmor(const character *a, const character *b);
int compareByName(const character *a, const character *b);
int compareByElement(const character *a, const character *b);
char *getSortField();
int chooseSort();
void sortCharacters(character *characters, int size);
void Remove(character *characters, int *len);
void menu(character *characters, int size);


