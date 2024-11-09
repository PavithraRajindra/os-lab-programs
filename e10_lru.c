// Page Replacement Policy - LRU
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

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int nf, n, faults = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the number of frames: ");
    scanf("%d", &nf);

    int frames[nf], pages[n], time[nf];
    
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
            int pos = findLRU(time, nf);

            for (int j = 0; j < nf; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

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