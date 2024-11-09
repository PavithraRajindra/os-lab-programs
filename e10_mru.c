// Page Replacement Policy - MRU
#include <stdio.h>

void printFrames(int frames[], int n) {
    printf("Frames: ");
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int findMRU(int time[], int n) {
    int max = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] > max) {
            max = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int n, nf, faults = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the number of frames: ");
    scanf("%d", &nf);

    int pages[n], frames[nf], time[nf];
    
    for (int i = 0; i < nf; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("\nPage Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < nf; j++) {
            if (frames[j] == page) {
                found = 1;
                time[j] = i + 1; 
                
                printf("Reference %d -> ", page);
                printFrames(frames, nf);
                break;
            }
        }

        if (!found) {
            int pos;

            for (pos = 0; pos < nf; pos++) {
                if (frames[pos] == -1)
                    break;
            }

            if (pos == nf)
                pos = findMRU(time, nf);

            frames[pos] = page;
            time[pos] = i + 1;
            faults++;

            printf("Reference %d -> ", page);
            printFrames(frames, nf);
        }
    }

    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}