#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cacheTable *createCache() {
    cacheTable *table = malloc(sizeof(cacheTable));
    table->size = MaxCacheSize;
    table->table = malloc(sizeof(cacheEntry *) * table->size);
    for (int i = 0; i < table->size; i++) {
        table->table[i] = NULL;
    }
    return table;
}

void readFile(cacheTable *cache, const char *filename, const char *domain) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error! Please, try again\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *found_dns = strtok(line, " \n");
        if (strcmp(found_dns, domain) == 0) {
            char *ip = strtok(NULL, " \n");
            addToCache(cache, domain, ip);
        }
    }
    fclose(fp);
}


void removeEntry(cacheTable *cache, cacheEntry *entry) {
    if (entry->prev == NULL) {
        //        cacheTable->head = entry->next;
    } else {
        entry->prev->next = entry->next;
    }
    if (entry->next == NULL) {
        //        cacheTable->tail = entry->prev;
    } else {
        entry->next->prev = entry->prev;
    }
    free(entry);
}

unsigned long hash(const char *str, unsigned int size) {
    unsigned long hash = size;
    int c;
    while ((c = (int) (*str++)))
        hash = ((hash << 5) + hash) + c;

    return hash % MaxCacheSize;
}

int isValidIP(char *IP) {
    int i = 0;
    char *copy = strdup(IP);
    char *token = strtok(copy, ".");
    while (token != NULL) {
        char *endptr;
        long val = strtol(token, &endptr, 10);
        if (*endptr != '\0' || val < 0 || val > 255) {
            return 0;// conversion error or out of range value
        }
        i++;
        token = strtok(NULL, ".");
    }
    if (i == 4) return 1;
    return 0;
}

void addToCache(cacheTable *cache, char *domain, char *IP) {
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
}

int getCacheEntry(cacheTable *table, const char *key) {
    int founded = 0;
    unsigned int index = hash(key, table->size);
    cacheEntry *current = table->table[index];
    while (current != NULL) {
        if (strcmp(current->domain, key) == 0) {
            if (isValidIP(current->IP) == 1)
                printf("Found IP: %s\n", current->IP);
            else
                getCache(table, current->IP);
            founded = 1;
        }
        current = current->next;
    }
    return founded;
}

void getCache(cacheTable *table, const char *key) {
    if (getCacheEntry(table, key) == 0)
        readFile(table, "../domens.txt", key);
    else {
        return;
    }
    getCacheEntry(table, key);
}

void printTable(cacheTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != NULL) {
            printf("%d: %s - %s\n", i, ht->table[i]->domain, ht->table[i]->IP);
        }
    }
}

int check(int key) {
    while (scanf_s("%d", &key) != 1 || key < 1 || key > 4) {
        fprintf(stderr, "Invalid input!");
        rewind(stdin);
    }
    return key;
}

void menu() {
    int key = 0;
    char *domain;
    domain = malloc(MaxDomainSize * sizeof(char));
    cacheTable *cache = createCache();
    printf("Input domen:");
    scanf_s("%s", domain);
    while (1) {
        printf("1-Add\n2-Find\n3-Print cache\n4-Exit\n");
        key = check(key);
        switch (key) {
            case 1: {
                char *ip = NULL;
                scanf_s("%15s", ip);
                addToCache(cache, domain, ip);
                break;
            }
            case 2:
                getCache(cache, domain);
                break;
            case 3:
                break;
            default:
                return;
        }
    }
}

int main() {
    /*    addToCache(cache, "example.com", "192.168.0.1");
    addToCache(cache, "google.com", "216.58.194.174");*/
    //    printTable(cache);
    //    removeEntry(cacheTable, "google.com");
    menu();
    return 0;
}
