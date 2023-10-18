#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";

    // Creating and writing to a file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    fprintf(file, "This is a sample text.\n");
    fclose(file);

    // Opening and reading from a file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    printf("File contents:\n");
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);

    // Appending data to a file
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    fprintf(file, "This is appended text.\n");
    fclose(file);

    // Reading the file after appending
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    printf("File contents after appending:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);

    return 0;
}

