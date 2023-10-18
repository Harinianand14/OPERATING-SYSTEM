#include <stdio.h>

// Define the maximum number of processes
#define MAX_PROCESSES 10

// Process structure to store process information
struct Process {
    int id;            // Process ID
    int burst_time;    // Burst time
    int remaining_time; // Remaining time
};

// Circular queue-like data structure to hold processes
struct Queue {
    struct Process* processes[MAX_PROCESSES];
    int front, rear;
};

// Function to enqueue a process into the queue
void enqueue(struct Queue* q, struct Process* process) {
    if ((q->rear + 1) % MAX_PROCESSES == q->front) {
        printf("Queue is full. Cannot enqueue more processes.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_PROCESSES;
    q->processes[q->rear] = process;
}

// Function to dequeue a process from the queue
struct Process* dequeue(struct Queue* q) {
    if (q->front == q->rear) {
        return NULL;
    }
    q->front = (q->front + 1) % MAX_PROCESSES;
    return q->processes[q->front];
}

// Function to simulate Round Robin scheduling
void roundRobinScheduling(struct Process processes[], int n, int time_slice) {
    struct Queue q;
    q.front = 0;
    q.rear = 0;

    int total_time = 0;

    // Enqueue all processes initially
    for (int i = 0; i < n; i++) {
        enqueue(&q, &processes[i]);
    }

    printf("Process Execution Order:\n");
    printf("Process\tRemaining Time\n");

    while (q.front != q.rear) {
        struct Process* current_process = dequeue(&q);

        if (current_process->remaining_time <= time_slice) {
            // Process can be completed within the time slice
            total_time += current_process->remaining_time;
            printf("%d\t%d\n", current_process->id, total_time);

        } else {
            // Process still has remaining time
            total_time += time_slice;
            current_process->remaining_time -= time_slice;
            enqueue(&q, current_process);
        }
    }
}

int main() {
    int n, time_slice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter the time slice: ");
    scanf("%d", &time_slice);

    roundRobinScheduling(processes, n, time_slice);

    return 0;
}

