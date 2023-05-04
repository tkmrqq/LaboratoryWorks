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
    cacheEntry **table;//ps arr
} cacheTable;

#define MaxCacheSize 5
#define MaxLineLength 256
#define MaxDomainSize 100
#define IPSize 15

cacheTable *createCache();
int isValidIP(const char *IP);
int getCacheEntry(cacheTable *table, const char *key);
void getCache(cacheTable *table, const char *key);
void addToCache(cacheTable *table, const char *domain, const char *IP);
void readFile(cacheTable *cache, const char *filename, const char *domain, const char *domainT);
void isEntry(const char *filename, const char *IP, const char *domain);
void printDomains(const char *IP, const char *filename);
void findDomains(const char *IP, const char *filename);
void printCache(cacheTable *cache);
void freeCache(cacheTable *cache);

#endif//LAB5_LIB_H
