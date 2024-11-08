// IPC using Shared memory
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key = ftok("shmfile",65);
    
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    if(shmid==-1){
        perror("shmget failed");
        exit(1);
    }
    
    char* str = (char*)shmat(shmid,NULL,0);
    if(str==(char*)-1)
    {
        perror("shmat failed");
        exit(1);
    }
    
    printf("Write Data: ");
    fgets(str, 1024, stdin);
    
    printf("Data written in memory:\n%s",str);
    return 0;
    
    printf("Press any key to detach process from shared memory!");
    getchar(str);
    shmdt()
    
    return 0;
}
