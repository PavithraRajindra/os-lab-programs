// Deadlock Detection
#include <stdio.h>
#include <stdlib.h>

int main() {
    int numProc, numReso;

    printf("Enter the number of processes: ");
    scanf("%d", &numProc);
    printf("Enter the number of resources: ");
    scanf("%d", &numReso);

    int allocation[numProc][numReso];
    int req[numProc][numReso];
    int available[numReso];

    printf("\nEnter the Allocation matrix:\n");
    for (int i = 0; i < numProc; i++) {
        for (int j = 0; j < numReso; j++) {
            printf("Allocation[%d][%d]: ", i, j);
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter the Request matrix:\n");
    for (int i = 0; i < numProc; i++) {
        for (int j = 0; j < numReso; j++) {
            printf("Maximum[%d][%d]: ", i, j);
            scanf("%d", &req[i][j]);
        }
    }

    printf("\nEnter the Available Resources:\n");
    for (int i = 0; i < numReso; i++) {
        printf("Available[%d]: ", i);
        scanf("%d", &available[i]);
    }

    int work[numReso];
    int finish[numProc];

    for (int i = 0; i < numReso; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < numProc; i++) {
        finish[i] = 0;
    }

    int deadlocked[numProc];
    int deadlock_count = 0;

    int change = 1;
    while (change) {
        change = 0;
        for (int i = 0; i < numProc; i++) {
            if (finish[i] == 0) {
                int possible = 1;
                for (int j = 0; j < numReso; j++) {
                    if (req[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < numReso; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    change = 1;
                }
            }
        }
    }

    for (int i = 0; i < numProc; i++) {
        if (finish[i] == 0)
            deadlocked[deadlock_count++] = i;
    }

    if (deadlock_count == 0) {
        printf("\nNo deadlocks detected\n");
    } else {
        printf("\nDeadlocked processes: ");
        for (int i = 0; i < deadlock_count; i++) {
            printf("P%d ", deadlocked[i]);
        }
        printf("\n");
    }

    return 0;
}