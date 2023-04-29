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

void addToCache(cacheTable *cache, const char *domain, char *IP) {
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

/*void calculateWithCache(key) {
    curTime = getCurrentTime();
    // Если значение уже было в кэше вернем его
    if (key in hashTable) {
        // Сначала обновим время последнего запроса к key
        timeQueue.set(key, curTime);
        return hashTable[key];
    }
    // Иначе вычислим результат
    result = calculate(key);

    // Если в кэше уже N элементов, то вытесним самый старый
    if (hashTable.length == N) {
        minKey = timeQueue.extractMinValue();
        hashTable.remove(minKey);
    }

    // Добавим в таблицу, и в очередь
    hashTable.add(key, result);
    timeQueue.add(key, curTime);

    return result;
}*/

int getCacheEntry(cacheTable *table, const char *key) {
    int founded = 0;
    unsigned int index = hash(key, table->size);
    cacheEntry *current = table->table[index];
    while (current != NULL) {
        if (strcmp(current->domain, key) == 0) {
            if (isValidIP(current->IP) == 1)
                printf("\033[0;32mFound IP: %s\033[0m\n", current->IP);
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
        readFile(table, "../domains.txt", key);
    else {
        return;
    }
    getCacheEntry(table, key);
}

void printCache(cacheTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != NULL) {
            printf("%d: %s - %s\n", i, ht->table[i]->domain, ht->table[i]->IP);
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