// Deadlock Avoidance - Banker's Algorithm
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int numProc,numReso;

    printf("Enter the number of processes: ");
    scanf("%d",&numProc);
    printf("Enter the number of resources: ");
    scanf("%d",&numReso);

    int allocation[numProc][numReso];
    int max[numProc][numReso];
    int available[numReso];

    printf("\nEnter the Allocation matrix:\n");
    for(int i=0;i<numProc;i++)
    {
        for(int j=0;j<numReso;j++)
        {
            printf("Allocation[%d][%d]: ",i,j);
            scanf("%d",&allocation[i][j]);
        }
    }

    printf("\nEnter the Maximum matrix:\n");
    for(int i=0;i<numProc;i++)
    {
        for(int j=0;j<numReso;j++)
        {
            printf("Maximum[%d][%d]: ",i,j);
            scanf("%d",&max[i][j]);
        }
    }

    printf("\nEnter the Available Resources:\n");
    for(int i=0;i<numReso;i++)
    {
        printf("Available[%d]: ",i);
        scanf("%d",&available[i]);
    }

    int need[numProc][numReso];
    for(int i=0;i<numProc;i++)
    {
        for(int j=0;j<numReso;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];  
        }
    }

    printf("\nNeed Matrix:\n");
    for(int i=0;i<numProc;i++)
    {
        for(int j=0;j<numReso;j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    int work[numReso];
    int finish[numProc];
    int safeSeq[numProc];
    int count=0;

    for(int i=0;i<numReso;i++)
    {
        work[i]=available[i];
    }
    for(int i=0;i<numProc;i++)
    {
        finish[i]=0;
    }

    while(count<numProc)
    {
        int found=0;
        for(int i=0;i<numProc;i++)
        {
            if(finish[i]==0)
            {
                int j;
                for(j=0;j<numReso;j++)
                {
                    if(need[i][j]>work[j])
                        break;
                }
                if(j==numReso)
                {
                    safeSeq[count++]=i;
                    finish[i]=1;
                    found=1;

                    for(j=0;j<numReso;j++)
                    {
                        work[j]+=allocation[i][j];
                    }
                }
            }
            if(found==0)
            {
                printf("\nSystem is not in safe state\n");
                return 1;
            }
        }
    }

    printf("\nSystem is in safe state\nSade sequence is ");
    for(int i=0;i<numProc;i++)
    {
        printf("P%d",safeSeq[i]);
    }
    printf("\n");
    return 0;
}