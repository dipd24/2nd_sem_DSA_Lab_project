#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_QUEUE_SIZE 10
#define MAX_NAME_LENGTH 50

typedef struct {
    char jobs[MAX_QUEUE_SIZE][MAX_NAME_LENGTH];
    int front, rear;
} PrintQueue;

void initializeQueue(PrintQueue *q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(PrintQueue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

int isEmpty(PrintQueue *q) {
    return q->front == -1;
}

void addJob(PrintQueue *q, char *jobName) {
    if (isFull(q)) {
        printf("\n\n Queue is full! Cannot add job.");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    strncpy(q->jobs[q->rear], jobName, MAX_NAME_LENGTH);
    printf("\n\n***Job \"%s\" added to the queue.***\n\n", jobName);
}

void processJob(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("\n\n*** No print jobs in the queue.***\n\n");
        return;
    }

    char *currentJob = q->jobs[q->front];

    printf("\n\nPrinting \"%s\"...\n", currentJob);
    sleep(2);

    // Simulate printed content
    printf("\n---- Printed Content ----\n");
    for (int i = 0; i < 3; i++) {
        printf("%s - Line %d\n", currentJob, i + 1);
        sleep(1);
    }
    printf("-------------------------\n");

    printf("\n***\"%s\" printed successfully!***\n\n", currentJob);

    if (q->front == q->rear) {
        initializeQueue(q);
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }
}

void viewQueue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("\n\n***The print queue is empty.***\n\n");
        return;
    }
    printf("\n\n ###Current print queue:");
    int i = q->front;
    int count = 1;
    while (1) {
        printf("\n  %d. %s", count++, q->jobs[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("\n\n");
}

int main() {
    PrintQueue printer;
    initializeQueue(&printer);
    int choice;
    char jobName[MAX_NAME_LENGTH];

    while (1) {
        printf("\n========================");
        printf("\n*** Print Queue Menu ***");
        printf("\n========================");
        printf("\n1. Add Print Job");
        printf("\n2. Process Next Job");
        printf("\n3. View Print Queue");
        printf("\n4. Exit");
        printf("\n========================");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter document name: ");
                fgets(jobName, MAX_NAME_LENGTH, stdin);
                jobName[strcspn(jobName, "\n")] = 0; // Remove newline
                addJob(&printer, jobName);
                break;
            case 2:
                processJob(&printer);
                break;
            case 3:
                viewQueue(&printer);
                break;
            case 4:
                printf("\n\n***Exiting print queue system. Goodbye!***\n\n");
                return 0;
            default:
                printf("\n\n***Invalid choice! Please select again.***\n\n");
        }
    }
}



