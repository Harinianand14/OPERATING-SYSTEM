#include <stdio.h>

#define MEMORY_SIZE 100

// Structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
    int allocated;
};

// Function to initialize the memory blocks
void initializeMemory(struct MemoryBlock memory[], int size) {
    for (int i = 0; i < size; i++) {
        memory[i].id = i + 1;
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

// Function to display the memory status
void displayMemory(struct MemoryBlock memory[], int size) {
    printf("Memory Block\tSize\tStatus\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t\t%d\t%s\n", memory[i].id, memory[i].size,
               memory[i].allocated ? "Allocated" : "Free");
    }
}

// Function to allocate memory using First Fit algorithm
int allocateMemory(struct MemoryBlock memory[], int size, int requestSize) {
    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = 1;
            return i;
        }
    }
    return -1; // Memory allocation failed
}

// Function to deallocate memory
void deallocateMemory(struct MemoryBlock memory[], int index) {
    memory[index].allocated = 0;
}

int main() {
    struct MemoryBlock memory[MEMORY_SIZE];
    initializeMemory(memory, MEMORY_SIZE);

    int choice, size;
    int index;

    do {
        printf("\n1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Display Memory Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the size of the memory block to allocate: ");
                scanf("%d", &size);
                index = allocateMemory(memory, MEMORY_SIZE, size);
                if (index != -1) {
                    printf("Memory allocated at block %d\n", memory[index].id);
                } else {
                    printf("Memory allocation failed. No suitable block found.\n");
                }
                break;
            case 2:
                printf("Enter the block number to deallocate: ");
                scanf("%d", &index);
                if (index >= 1 && index <= MEMORY_SIZE) {
                    if (memory[index - 1].allocated) {
                        deallocateMemory(memory, index - 1);
                        printf("Memory block %d deallocated.\n", index);
                    } else {
                        printf("Memory block %d is already free.\n", index);
                    }
                } else {
                    printf("Invalid block number.\n");
                }
                break;
            case 3:
                displayMemory(memory, MEMORY_SIZE);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

