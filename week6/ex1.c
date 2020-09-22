// Ex.1: FCFS
#include <stdio.h>
#include <stdlib.h>

void sort(int *keys, int* values, int length) {
    // Bubble sort for 2 arrays, using one of them as a primary for comparison
    int tmpkey, tmpval;
    for (unsigned int i = length - 1; i > 0; i--) {
        for (unsigned int j = 0; j < i; j++) {
            if (keys[j] > keys[j+1]) {
                // swap in both arrays
                tmpkey = keys[j];
                tmpval = values[j];
                keys[j] = keys[j+1];
                values[j] = values[j+1];
                keys[j+1] = tmpkey;
                values[j+1] = tmpval;
            }
        }
    }
}

int main() {
    int count;
    printf("Enter the number of processes: ");
    scanf("%d", &count);
    
    int *arrival = malloc(count * sizeof(int));
    int *service = malloc(count * sizeof(int));  //a.k.a. burst time
    int *started = malloc(count * sizeof(int));
    
    if (arrival == NULL || service == NULL || started == NULL) {
        fprintf(stderr, "Failed to allocate the memory, exiting\n");
        free(arrival);
        free(service);
        free(started);
        return 1;
    }
    
    printf("Enter the arrival time and burst (service) time values (e.g. \"1 4\"): ");
    for (unsigned int i = 0; i < count; i++) {
        scanf("%d", arrival+i);
        scanf("%d", service+i);
    }
    sort(arrival, service, count);
    
    for (unsigned int i = 0; i < count; i++) {
        started[i] = arrival[i];
        if (i > 0 && started[i-1] + service[i-1] > started[i]) {
            started[i] = started[i-1] + service[i-1];  // CT of the previous process
        }
    }
    
    float sumTAT = 0, sumWT = 0;
    printf("The processes (sorted by arrival time):\n");
    printf("P#:\tAT:\tBT:\tCT:\tTAT:\tWT:\n");
    for (unsigned int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            i+1, arrival[i], service[i], // P#, AT, BT
            started[i] + service[i], started[i] + service[i] - arrival[i], started[i] - arrival[i]);  // CT, TAT, WT
        sumTAT += started[i] + service[i] - arrival[i];
        sumWT  += started[i] - arrival[i];
    }
    printf("\nAverage TAT: %f\n", sumTAT / count);
    printf("Average WT: %f\n", sumWT / count);
    
    free(arrival);
    free(service);
    free(started);
    return 0;
}
