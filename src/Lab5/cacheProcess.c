#include "lib.h"

cacheTable *createCache() {
    cacheTable *table = malloc(sizeof(cacheTable));
    table->size = MaxCacheSize;
    table->table = malloc(sizeof(cacheEntry *) * table->size);
    for (int i = 0; i < table->size; i++) {
        table->table[i] = NULL;
    }
    return table;
}

unsigned long hash(const char *str, unsigned int size) {
    unsigned long hash = size;
    int c;
    while ((c = (int) (*str++)))
        hash = ((hash << 5) + hash) + c;
    return hash % MaxCacheSize;
}

/*void addToCache(cacheTable *cache, const char *domain, char *IP) {
    unsigned int index = hash(domain, cache->size);
    cacheEntry *entry = malloc(sizeof(cacheEntry));
    entry->domain = strdup(domain);
    entry->IP = strdup(IP);
    entry->prev = NULL;
    entry->next = cache->table[index];
    if (cache->table[index] != NULL) {
        cache->table[index]->prev = entry;
    }
    cache->table[index] = entry;
}*/

void addToCache(cacheTable *table, const char *domain, const char *IP) {
    unsigned int index = hash(domain, table->size);
    cacheEntry *entry = malloc(sizeof(cacheEntry));
    entry->domain = strdup(domain);
    entry->IP = strdup(IP);
    int count = 0;
    if (table->table[index] != NULL) {
        cacheEntry *current = table->table[index];
        while (current != NULL) {
            count++;
            if (count >= MaxCacheSize - 1 && current->next != NULL) {
//                printf("REMOVING: %s\n", current->next->domain);
                free(current->next);
                current->next = NULL;
                break;
            }
            current = current->next;
        }
    }
    entry->prev = NULL;
    entry->next = table->table[index];
    if (table->table[index] != NULL) {
        table->table[index]->prev = entry;
    }
    table->table[index] = entry;
}

int getCacheEntry(cacheTable *table, const char *key) {
    unsigned int index = hash(key, table->size);
    cacheEntry *current = table->table[index];
    cacheEntry *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->domain, key) == 0) {
            if (isValidIP(current->IP) == 1) {
                printf("\033[0;32mFound IP: %s\033[0m\n", current->IP);
            } else {
                getCache(table, current->IP);
            }

            if (prev != NULL) {
                prev->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = prev;
                }
                current->prev = NULL;
                current->next = table->table[index];
                table->table[index]->prev = current;
                table->table[index] = current;
            }

            cacheEntry *next = current->next;
            while (next != NULL) {
                next->prev = next->prev == current ? NULL : current;
                current->next = next;
                current->prev = prev;
                prev = current;
                current = next;
                next = next->next;
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void getCache(cacheTable *table, const char *key) {
    if (getCacheEntry(table, key) == 0)
        readFile(table, "../domains.txt", key, NULL);
    else {
        return;
    }
    getCacheEntry(table, key);
}

void printCache(cacheTable *cache) {
    printf("Cache Table:\n");
    for (int i = 0; i < cache->size; i++) {
        cacheEntry *current = cache->table[i];
        if (current != NULL) {
//            printf("  %d:\n", i);
            while (current != NULL) {
                printf("    %s -> %s\n", current->domain, current->IP);
                current = current->next;
            }
        }
    }
}

void freeCache(cacheTable *cache) {
    for (int i = 0; i < cache->size; i++) {
        cacheEntry *current = cache->table[i];
        while (current != NULL) {
            cacheEntry *next = current->next;
            free(current->domain);
            free(current->IP);
            free(current);
            current = next;
        }
    }
    free(cache->table);
    free(cache);
}