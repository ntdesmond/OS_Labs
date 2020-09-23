// Ex. 2: SJF
#include <stdio.h>
#include <stdlib.h>

struct process {
    int index;
    int arrival;
    int service;  //a.k.a. burst time
    int started;
};

void swap(struct process *array, int index1, int index2) {
    // Swap elements at index1 and index2 in a given array
    struct process tmp;
    tmp = array[index1];
    array[index1] = array[index2];
    array[index2] = tmp;
}

int main() {
    int count;
    printf("Enter the number of processes: ");
    scanf("%d", &count);
    
    struct process *processes = malloc(count * sizeof(struct process));
    
    if (processes == NULL) {
        fprintf(stderr, "Failed to allocate the memory, exiting\n");
        free(processes);
        return 1;
    }
    
    printf("Enter the arrival time and burst (service) time values (e.g. \"1 4\"): ");
    for (unsigned int i = 0; i < count; i++) {
        int arrival, service;
        scanf("%d", &arrival);
        scanf("%d", &service);
        struct process tmp = {i+1, arrival, service, -1};
        processes[i] = tmp;
    }
    
    int time = 0, shortest;
    for (unsigned int i = 0; i < count; i++) {
        // Find the shortest job that is ready to be started
        shortest = i;
        for (unsigned int j = i+1; j < count; j++) {
            if (processes[j].arrival <= time && processes[j].service < processes[shortest].service) {
                shortest = j;
            }
        }
        
        // Schedule the job and forward the time to its CT
        processes[shortest].started = time;
        time += processes[shortest].service;
        
        // Don't consider this job/process anymore
        if (shortest != i) {
            swap(processes, shortest, i);
        }
    }
    
    float sumTAT = 0, sumWT = 0;
    printf("The processes:\n");
    printf("P#:\tAT:\tBT:\tCT:\tTAT:\tWT:\n");
    for (unsigned int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            processes[i].index, processes[i].arrival, processes[i].service,      // P#, AT, BT
            processes[i].started + processes[i].service,                         // CT
            processes[i].started + processes[i].service - processes[i].arrival,  // TAT
            processes[i].started - processes[i].arrival);                        // WT
        sumTAT += processes[i].started + processes[i].service - processes[i].arrival;
        sumWT  += processes[i].started - processes[i].arrival;
    }
    printf("\nAverage TAT: %f\n", sumTAT / count);
    printf("Average WT: %f\n", sumWT / count);
    
    free(processes);
    return 0;
}
