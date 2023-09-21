#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

#define BUFFER_SIZE 10

Queue buffer;
sem_t empty, full;
pthread_mutex_t mutex;

int item_counter = 0;

void enqueue(Queue* q, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue* q) {
    if (q->front == NULL) {
        return -1; // empty
    }
    int item = q->front->data;
    Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return item;
}

void print_buffer() {
    Node* current = buffer.front;
    printf("Buffer: [");
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;
        if (current != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

void *producer(void *arg) {
    int item;
    int producer_id = *(int*)arg;
    for (int i = 0; i < 5; i++) {
        item = rand() % 10; 
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        enqueue(&buffer, item);
        printf("Producer %d produced item %d\n",producer_id, item);
        print_buffer();
        
        item_counter++; // debug
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 8); 
        sem_post(&full);
        
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    int consumer_id = *(int*)arg;
    for (int i = 0; i < 5; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = dequeue(&buffer);
        printf("Consumer %d consumed item %d\n", consumer_id, item);
        print_buffer();
        
        item_counter--;
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 8); 
        sem_post(&empty);
        
    }
    return NULL;
}

int main() {
    pthread_t producers[3];
    pthread_t consumers[4];
    int prod_ids[3] = {1, 2, 3};
    int cons_ids[4] = {1, 2, 3, 4};
	// empty full mutex initialilze
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    buffer.front = buffer.rear = NULL; // Initialize the queue

    for (int i = 0; i < 3; i++) {
        pthread_create(&producers[i], NULL, producer, &prod_ids[i]);
        sleep(1);
    }

    for (int i = 0; i < 4; i++) {
        pthread_create(&consumers[i], NULL, consumer, &cons_ids[i]);
        sleep(1);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(consumers[i], NULL);
    }

}
