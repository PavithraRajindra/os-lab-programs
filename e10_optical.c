// Page Replacement Policy - Optical
#include <stdio.h>

void printFrames(int frames[], int n) {
    printf("Frames: ");
    for(int i = 0; i < n; i++) {
        if(frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int findOptimal(int pages[], int frames[], int nf, int n, int index) {
    int pos = -1, farthest = index;
    for(int i = 0; i < nf; i++) {
        int j;
        // Find when this frame will be used in future
        for(j = index; j < n; j++) {
            if(frames[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        // If page will not be used in future
        if(j == n)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int n, nf, faults = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the number of frames: ");
    scanf("%d", &nf);

    int frames[nf], pages[n];

    for(int i = 0; i < nf; i++)
        frames[i] = -1;

    printf("Enter the page reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("\nPage Replacement Process:\n");

    for(int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for(int j = 0; j < nf; j++) {
            if(frames[j] == page) {
                found = 1;
                printf("Reference %d -> ", page);
                printFrames(frames, nf);
                break;
            }
        }

        if(!found) {
            int pos;
            for(pos = 0; pos < nf; pos++) {
                if(frames[pos] == -1)
                    break;
            }

            if(pos == nf)
                pos = findOptimal(pages, frames, nf, n, i + 1);

            frames[pos] = page;
            faults++;
            printf("Reference %d -> ", page);
            printFrames(frames, nf);
        }
    }

    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}