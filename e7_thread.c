// Creation of Threads
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* threadFunc(int* arg)
{
    int threadNum =*((int*)arg);
    printf("Hello from thread %d",threadNum);
    return NULL;
}

int main()
{
    int n;

    printf("Enter number of threads to be created: ");
    scanf("%d",&n);

    pthread_t threads[n];
    int threadArgs[n];

    for(int i=0;i<n;i++)
    {
        if(pthread_create(&threads[i], NULL, threadFunc, threadArgs[i])!=0)
        {
            perror("Thread creation failed");
            return 1;
        }
    }

    for(int i=0;i<n;i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished execution");
    return 0;
}