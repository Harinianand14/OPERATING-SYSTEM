#include <stdio.h>

#define MEMORY_SIZE 100
#define MAX_PROCESS 10

int memory[MEMORY_SIZE];
int processSize[MAX_PROCESS];
int processAllocated[MAX_PROCESS];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0; // Initialize all memory locations to 0
    }
}

void bestFit(int n) {
    for (int i = 0; i < n; i++) {
        int bestBlockSize = MEMORY_SIZE + 1; // Initialize to a large value
        int bestBlockIndex = -1;

        for (int j = 0; j < MEMORY_SIZE; j++) {
            int blockSize = 0;
            while (j < MEMORY_SIZE && memory[j] == 0) {
                blockSize++;
                j++;
            }

            if (blockSize >= processSize[i] && blockSize < bestBlockSize) {
                bestBlockSize = blockSize;
                bestBlockIndex = j - blockSize;
            }
        }

        if (bestBlockIndex != -1) {
            for (int j = bestBlockIndex; j < bestBlockIndex + processSize[i]; j++) {
                memory[j] = i + 1;
            }
            processAllocated[i] = bestBlockIndex;
        } else {
            processAllocated[i] = -1; // Process could not be allocated
        }
    }
}

void displayMemory() {
    printf("Memory Allocation:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == 0) {
            printf("- ");
        } else {
            printf("%d ", memory[i]);
        }
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    initializeMemory();
    bestFit(n);

    printf("\nMemory after best fit allocation:\n");
    displayMemory();

    printf("\nProcess Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (processAllocated[i] != -1) {
            printf("Process %d is allocated at position %d\n", i + 1, processAllocated[i]);
        } else {
            printf("Process %d could not be allocated\n", i + 1);
        }
    }

    return 0;
}

