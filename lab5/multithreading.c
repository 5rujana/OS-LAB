#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *printHi(void *arg) {
    for (int i = 0; i < 5; i++) {
        printf("Hi\n");
        usleep(1000000); // sleep for 1 second
    }
    return NULL;
}

void *printHello(void *arg) {
    for (int i = 0; i < 5; i++) {
        printf("Hello\n");
        usleep(1000000); // sleep for 1 second
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    printf("Before Threads\n");

    pthread_create(&t1, NULL, printHi, NULL);
    usleep(10000); // sleep for 10 milliseconds
    pthread_create(&t2, NULL, printHello, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("After Threads\n");

    return 0;
}
