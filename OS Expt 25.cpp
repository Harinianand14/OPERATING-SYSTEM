#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // fcntl - File control
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    // Perform an operation with fcntl (for example, setting the file to non-blocking)
    int flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        perror("fcntl");
        exit(1);
    }
    close(fd);

    // lseek - File offset control
    fd = open("example.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    off_t offset = lseek(fd, 10, SEEK_SET); // Move the file offset to the 10th byte
    if (offset == -1) {
        perror("lseek");
        exit(1);
    }
    close(fd);

    // stat - File status
    struct stat fileStat;
    if (stat("example.txt", &fileStat) == -1) {
        perror("stat");
        exit(1);
    }
    printf("File size: %lld bytes\n", (long long)fileStat.st_size);

    // opendir and readdir - Directory operations
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;
    printf("Files in the current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return 0;
}

