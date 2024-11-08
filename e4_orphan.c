// Creation of Orphan Process
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if(pid==-1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if(pid==0){
        printf("Child process is sleeping...");
        sleep(10);
        printf("Child process (orphan) is continuing...");
    }
    else{
        printf("Parent process is exiting...");
        exit(0);
    }

    return 0;
}