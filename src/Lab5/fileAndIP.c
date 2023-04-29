#include "lib.h"

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

int isValidIP(const char *IP) {
    int i = 0;
    char *copy = strdup(IP);
    char *token = strtok(copy, ".");
    while (token != NULL) {
        char *endPtr;
        long val = strtol(token, &endPtr, 10);
        if (*endPtr != '\0' || val < 0 || val > 255) {
            return 0;
        }
        i++;
        token = strtok(NULL, ".");
    }
    if (i == 4) return 1;
    return 0;
}

void isEntry(const char *filename, const char *IP, const char *domain) {
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("Invalid input!\n");
        return;
    }
    char line[MaxCacheSize];
    char *current_dns;
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *savePtr = NULL;
        current_dns = strtok_r(line, " ", &savePtr);
        if (strcmp(current_dns, domain) == 0) {
            printf("IP address '%s' already exists\n", domain);
            fclose(fp);
            return;
        }
    }
    fseek(fp, 0, SEEK_END);
    if (isValidIP(IP) == 1) {
        fprintf(fp, "\n%s %s", domain, IP);
        fclose(fp);
    }
}

void findDomain(const char *IP, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    char line[MaxCacheSize / 4];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *savePtr = NULL;
        char *domain = strtok_r(line, " \n", &savePtr);
        char *ip = strtok_r(NULL, " \n", &savePtr);
        if (strcmp(ip, IP) == 0) {
            printf("\033[0;33m%s\033[0m\n", domain);
        }
    }
    fclose(file);
}

void findDomains(char* ip_addr, cacheTable * cache) {
    int i;
    cacheEntry *cacheEntry;
    for (i = 0; i < cache->size; i++) {
        cacheEntry = cache->table[i];
        while (cacheEntry != NULL) {
            if (strcmp(cacheEntry->IP, ip_addr) == 0) {
                printf("\033[0;33m%s\033[0m\n", cacheEntry->domain);
            }
            cacheEntry = cacheEntry->next;
        }
    }
}