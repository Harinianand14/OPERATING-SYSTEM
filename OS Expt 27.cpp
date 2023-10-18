#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char *dir_path;

    if (argc == 1) {
        dir_path = "."; // Default to the current directory
    } else if (argc == 2) {
        dir_path = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        exit(1);
    }

    DIR *dir;
    struct dirent *entry;

    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

    printf("Listing of directory: %s\n", dir_path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return 0;
}

