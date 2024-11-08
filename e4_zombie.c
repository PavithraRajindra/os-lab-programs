// Creation of Zombie process
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    pid_t pid;

    pid=fork();
    if(pid==-1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    
    if(pid==0)
    {
        printf("Child process exiting...\n");
        exit(0);
    }
    else{
        printf("Parent process sleeping...\n");
        sleep(10);
        printf("Parent process finished\n");
    }
    
    return 0;
}