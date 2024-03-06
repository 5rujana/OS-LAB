#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t chopstick[5];
sem_t room;

void *philosopher(void *arg)
{
    int i = *(int *)arg;
    printf("Philosopher %d is thinking\n", i);
    sleep(2);
    sem_wait(&room);
    printf("Philosopher %d is hungry\n", i);
    sem_wait(&chopstick[i]);
    sem_wait(&chopstick[(i+1)%5]);
    sem_post(&room);
    printf("Philosopher %d is eating\n", i);
    sleep(2);
    sem_post(&chopstick[i]);
    sem_post(&chopstick[(i+1)%5]);
    printf("Philosopher %d finished eating\n", i);
}

int main()
{
    pthread_t phil[5];
    sem_init(&room, 0, 4);
    for(int i=0; i<5; i++)
        sem_init(&chopstick[i], 0, 1);
    int a[5] = {0, 1, 2, 3, 4};
    for(int i=0; i<5; i++)
        pthread_create(&phil[i], NULL, philosopher, (void *)&a[i]);
    for(int i=0; i<5; i++)
        pthread_join(phil[i], NULL);
    return 0;
}

