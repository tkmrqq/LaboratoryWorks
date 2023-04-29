#ifndef LAB5_LIB_H
#define LAB5_LIB_H

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

#define MaxCacheSize 1024
#define MaxDomainSize 100

int getCacheEntry(cacheTable *table, const char *key);
void getCache(cacheTable *table, const char *key);
void addToCache(cacheTable *cache, char *domain, char *IP);

#endif//LAB5_LIB_H
