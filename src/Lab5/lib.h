#ifndef LAB5_LIB_H
#define LAB5_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cacheEntry {
    char *domain;
    char *IP;
    struct cacheEntry *next;
    struct cacheEntry *prev;
} cacheEntry;

typedef struct cache {
    int size;
    cacheEntry **table;
} cacheTable;

#define MaxCacheSize 5
#define MaxDomainSize 100
#define IPSize 15

cacheTable *createCache();
int isValidIP(const char *IP);
int getCacheEntry(cacheTable *table, const char *key);
void getCache(cacheTable *table, const char *key);
void addToCache(cacheTable *cache, const char *domain, char *IP);
void readFile(cacheTable *cache, const char *filename, const char *domain);
void addToFile(const char *filename, const char *IP, const char *domain);
void isEntry(const char *filename, const char *IP, const char *domain);
void findDomain(const char* IP, const char* filename);
void printCache(cacheTable *ht);
void freeCache(cacheTable *cache);

void findDomains(char* ip_addr, cacheTable * cache);


#endif//LAB5_LIB_H
