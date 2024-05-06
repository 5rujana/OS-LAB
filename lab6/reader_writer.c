//read write problem
#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

sem_t x,y;
pthread_t tid;
pthread_t wt[100],rt[100];
int readcount=0;

void *reader(void *param){
    sem_wait(&x);
    readcount++;
    if(readcount==1)
        sem_wait(&y);
    sem_post(&x);
    printf("%d reader is inside\n",readcount);
    usleep(3);
    sem_wait(&x);
    readcount--;
    if(readcount==0)
        sem_post(&y);
    sem_post(&x);
    printf("%d Reader is leaving \n", readcount+1);
    return NULL;
}

void *writer(void *param){
    printf("Writer is trying to enter \n");
    sem_wait(&y);
    printf("writer has entered\n");
    sem_post(&y);
    printf("writer is leaving\n");
    return NULL;
}

int main(){
    int n2,i;
    printf("Enter the number of readers: ");
    scanf("%d",&n2);
    printf("\n");
    int n1[n2];
    sem_init(&x,0,1);
    sem_init(&y,0,1);
    for(i=0;i<n2;i++){
        pthread_create(&wt[i],NULL,writer,NULL);
        pthread_create(&rt[i],NULL,reader,NULL);
    }
    for(i=0;i<n2;i++){
        pthread_join(wt[i],NULL);
        pthread_join(rt[i],NULL);
    }
}

