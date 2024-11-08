// Page Replacement Policy - FIFO
#include<stdio.h>
#include<stdlib.h>

void printFrames(int frames[], int n)
{
    for(int i=0;i<n;i++)
    {
        if(frames[i]==-1){
            printf("- ");
        }
        else{
            printf("%d ",frames[i]);
        }
    }
    printf("\n");
}

int main()
{
    int n, nf;

    printf("Enter number of pages: ");
    scanf("%d",&n);
    printf("Enter number of frames: ");
    scanf("%d",&nf);

    int pages[n];
    int frames[nf];

    for(int i=0;i<nf;i++)
    {
        frames[i]=-1;
    }

    printf("Enter page reference string: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }

    int pageFaults=0;
    int cur=0;

    printf("Page Replacement Process: ");
    for(int i=0;i<n;i++)
    {
        int page=pages[i];
        int found = 0;
        
        for(int j=0;j<nf;j++)
        {
            if(frames[j]==page)
            {
                found=1;
                printf("Reference %d: ",page);
                printFrames(frames,nf);
                break;
            }
        }

        if(!found)
        {
            frames[cur]=page;
            cur=(cur+1)%nf;
            pageFaults++;
            printf("Reference %d: ",page);
            printFrames(frames,nf);
        }
    }

    printf("Total Page Faults: %d\n",pageFaults);
    return 0;
}