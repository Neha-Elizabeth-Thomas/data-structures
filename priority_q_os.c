#include <stdio.h>
#include <stdlib.h>

// Structure to represent a task
struct Task {
    char name;
    int priority;
    int execution_time;
    int waiting_time;
};

// Structure to represent a node in the priority queue
struct PriorityQueueNode {
    struct Task task;
    struct PriorityQueueNode* next;
};

// Priority Queue structure
struct PriorityQueue {
    struct PriorityQueueNode* front;
};

// Queue structure for waiting tasks
struct QueueNode {
    struct Task task;
    struct QueueNode* next;
};

// Queue structure
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to initialize an empty priority queue
struct PriorityQueue* createPriorityQueue() {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->front = NULL;
    return pq;
}

// Function to check if the priority queue is empty
int isPriorityQueueEmpty(struct PriorityQueue* pq) {
    return (pq->front == NULL);
}

// Function to insert a task into the priority queue based on waiting time and priority
void insertPriorityQueue(struct PriorityQueue* pq, struct Task task) {
    struct PriorityQueueNode* newNode = (struct PriorityQueueNode*)malloc(sizeof(struct PriorityQueueNode));
    newNode->task = task;
    newNode->next = NULL;

    // If the priority queue is empty or the new task has higher priority and longer waiting time
    if (isPriorityQueueEmpty(pq) || (task.priority > pq->front->task.priority) ||
        ((task.priority == pq->front->task.priority) && (task.waiting_time > pq->front->task.waiting_time))) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        struct PriorityQueueNode* current = pq->front;

        // Find the appropriate position to insert the new task
        while (current->next != NULL &&
               ((task.priority < current->next->task.priority) ||
                ((task.priority == current->next->task.priority) && (task.waiting_time <= current->next->task.waiting_time)))) {
            current = current->next;
        }

        // Insert the new task
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to remove and return the task with the highest priority and longest waiting time
struct Task dequeuePriorityQueue(struct PriorityQueue* pq) {
    if (isPriorityQueueEmpty(pq)) {
        // Return a dummy task if the priority queue is empty (simulation purposes)
        struct Task dummy = {'D', 0, 0, 0};
        return dummy;
    }

    struct PriorityQueueNode* temp = pq->front;
    struct Task task = temp->task;
    pq->front = pq->front->next;
    free(temp);
    return task;
}

// Function to initialize an empty queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* q) {
    return (q->front == NULL);
}

// Function to enqueue a task into the queue
void enqueueQueue(struct Queue* q, struct Task task) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->task = task;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Function to dequeue a task from the queue
struct Task dequeueQueue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        // Return a dummy task if the queue is empty (simulation purposes)
        struct Task dummy = {'D', 0, 0, 0};
        return dummy;
    }

    struct QueueNode* temp = q->front;
    struct Task task = temp->task;
    q->front = q->front->next;
    free(temp);
    return task;
}

// Function to simulate the time-sharing operating system
void simulateTimeSharing(struct PriorityQueue* pq, struct Queue* waitingQueue) {
    // Simulate tasks being introduced into the system randomly (for demonstration purposes)
    for (int i = 0; i < 10; i++) {
        struct Task newTask = {'A' + i, rand() % 10, rand() % 20 + 1, 0};
        enqueueQueue(waitingQueue, newTask);
        printf("Task %c introduced with priority %d and execution time %d ms\n", newTask.name, newTask.priority, newTask.execution_time);
    }

    int timeElapsed = 0;

    while (!isPriorityQueueEmpty(pq) || !isQueueEmpty(waitingQueue)) {
        // Move tasks from waiting queue to priority queue based on waiting time
        while (!isQueueEmpty(waitingQueue) && waitingQueue->front->task.waiting_time == timeElapsed) {
            insertPriorityQueue(pq, dequeueQueue(waitingQueue));
        }

        // Get the task with the highest priority and longest waiting time
        struct Task currentTask = dequeuePriorityQueue(pq);

        if (currentTask.execution_time > 0) {
            printf("Executing Task %c (Priority: %d, Execution Time Remaining: %d ms)\n", currentTask.name, currentTask.priority, currentTask.execution_time);

            // Update waiting time for the remaining tasks in the priority queue
            struct PriorityQueueNode* current = pq->front;
            while (current != NULL) {
                current->task.waiting_time++;
                current = current->next;
            }

            // Update the task's waiting time and remaining execution time
            currentTask.waiting_time = 0;
            currentTask.execution_time--;

            // Re-insert the task back into the priority queue
            insertPriorityQueue(pq, currentTask);
        }

        timeElapsed++;
    }
}

int main() {
    struct PriorityQueue* priorityQueue = createPriorityQueue();
    struct Queue* waitingQueue = createQueue();

    simulateTimeSharing(priorityQueue, waitingQueue);

    free(priorityQueue);
    free(waitingQueue);

    return 0;
}
