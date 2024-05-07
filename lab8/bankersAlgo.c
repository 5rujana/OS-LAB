//bankers algorithm
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int n, m;
int *available, **max, **allocation, **need;
sem_t mutex;

void *process(void *arg)
{
    int p = *((int *)arg);
    int i;
    sem_wait(&mutex);
    printf("Process %d is requesting resources\n", p);
    for (i = 0; i < m; i++)
    {
        if (need[p][i] > available[i])
        {
            printf("Process %d is waiting\n", p);
            sem_post(&mutex);
            return NULL;
        }
    }
    for (i = 0; i < m; i++)
    {
        available[i] -= need[p][i];
        allocation[p][i] += need[p][i];
        need[p][i] = 0;
    }
    printf("Process %d has been allocated resources\n", p);
    sem_post(&mutex);
    return NULL;
}

int main()
{
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    available = (int *)malloc(m * sizeof(int));
    max = (int **)malloc(n * sizeof(int *));
    allocation = (int **)malloc(n * sizeof(int *));
    need = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
    {
        max[i] = (int *)malloc(m * sizeof(int));
        allocation[i] = (int *)malloc(m * sizeof(int));
        need[i] = (int *)malloc(m * sizeof(int));
    }
    printf("Enter the available resources: ");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }
    printf("Enter the maximum resources: ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the allocated resources: ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    sem_init(&mutex, 0, 1);
    pthread_t tid[n];
    int p[n];
    for (i = 0; i < n; i++)
    {
        p[i] = i;
        pthread_create(&tid[i], NULL, process, &p[i]);
    }
    for (i = 0; i < n; i++)
    {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&mutex);
    return 0;
}
