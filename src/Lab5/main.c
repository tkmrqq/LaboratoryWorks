#include "lib.h"

int check(int key) {
    while (scanf_s("%d", &key) != 1 || key < 1 || key > 5) {
        fprintf(stderr, "Invalid input!\n");
        rewind(stdin);
    }
    return key;
}

char* getDomain(){
    char *domain;
    domain = malloc(MaxDomainSize * sizeof(char));
    printf("Input domain:");
    scanf_s("%s", domain);
    return domain;
}

char *getIP() {
    char *ip;
    ip = malloc(IPSize * sizeof(char));
    printf("Input IP-Address:");
    scanf_s("%15s", ip);
    return ip;
}

void menu() {
    int key = 0;
    cacheTable *cache = createCache();
    while (1) {
        printf("================\n");
        printf("1-Add\n2-Find\n3-Print cache\n4-Find domain by IP\n5-Exit\n");
        key = check(key);
        switch (key) {
            case 1: {
                char *ip = getIP();
                char *domain = getDomain();
                addToCache(cache, domain, ip);
                isEntry("../domains.txt", ip, domain);
                break;
            }
            case 2: {
                char* domain = getDomain();
                getCache(cache, domain);
                break;
            }
            case 3:
                printCache(cache);
                break;
            case 4: {
                char *ip = getIP();
                if (isValidIP(ip) == 0)
                    return;
                if(cache != NULL){
                    findDomain(ip, "../domains.txt");
                }
                else
                    findDomains(ip, cache);
                break;
            }
            default:
                freeCache(cache);
                return;
        }
    }
}

int main() {
    menu();
    return 0;
}
