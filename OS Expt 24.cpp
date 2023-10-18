#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd; // File descriptor
    char filename[] = "example.txt";
    char buffer[100];

    // Create a new file (if it doesn't exist) or truncate an existing file
    fd = creat(filename, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("creat");
        exit(1);
    }
    printf("File created or truncated successfully.\n");

    // Write data to the file
    const char *data = "This is a sample text.\n";
    if (write(fd, data, strlen(data)) == -1) {
        perror("write");
        exit(1);
    }
    printf("Data written to the file.\n");

    // Close the file
    close(fd);
    printf("File closed.\n");

    // Open the file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    printf("File opened for reading.\n");

    // Read and display the file contents
    ssize_t bytesRead;
    printf("File contents:\n");
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        perror("read");
        exit(1);
    }

    // Close the file
    close(fd);
    printf("File closed.\n");

    // Remove the file
    if (remove(filename) == -1) {
        perror("remove");
        exit(1);
    }
    printf("File removed successfully.\n");

    return 0;
}

