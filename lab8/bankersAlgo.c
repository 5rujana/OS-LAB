#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
sem_t empty;
sem_t full;
int buffer[5];
int in = 0;
int out = 0;

void *producer(void *arg)
{
    int item;
    for(int i=0; i<5; i++)
    {
        item = rand();
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Producer produced item %d at position %d\n", item, in);
        in = (in+1)%5;
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void *consumer(void *arg)
{
    int item;
    for(int i=0; i<5; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        printf("Consumer consumed item %d from position %d\n", item, out);
        out = (out+1)%5;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);
    }
}

int main()
{
    pthread_t prod, cons;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}

