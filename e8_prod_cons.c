#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count=0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg)
{
    for(int i=0;i<10;i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[count]=i;
        printf("Produced: %d\n",buffer[count]);
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg)
{
    for(int i=0;i<10;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        count--;
        printf("\tConsumed: %d\n",buffer[count]);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t prod, cons;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}