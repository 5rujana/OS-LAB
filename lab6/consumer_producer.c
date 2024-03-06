//producer and consumer problem using semaphores
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#define BUFFER_SIZE 10
#define MAX 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
sem_t empty, full, mutex;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = i;
        printf("Produced item %d at position %d\n", buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    int item, i;
    for (i = 0; i < MAX; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        printf("Consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    pthread_t tid1, tid2;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}
