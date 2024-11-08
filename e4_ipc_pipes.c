// IPC using pipes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int pipefd[2]; //0 - read, 1-write
    pid_t pid;

    if(pipe(pipefd)==-1)
    {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid==-1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if(pid==0)
    {
        close(pipefd[1]);
        char buffer[100];

        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer)-1);
        if(bytesRead==-1)
        {
            perror("Read from pipe failed");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead]='\0';
        printf("Child process received:\n%s",buffer);
        close(pipefd[0]);
    }else
    {
        close(pipefd[0]);
        const char *message = "Hello, child";
        ssize_t bytesWritten = write(pipefd[1],message, strlen(message));
        if(bytesWritten==-1)
        {
            perror("Write to pipe failed");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
    }

    return 0;
}