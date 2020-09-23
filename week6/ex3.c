// Ex. 3: Round robin
#include <stdio.h>
#include <stdlib.h>

struct process {
    int index;
    int arrival;
    int service;  //a.k.a. burst time
    int started;
    int remaining;
    int exit;
};

void swap(struct process *array, int index1, int index2) {
    // Swap elements at index1 and index2 in a given array
    struct process tmp;
    tmp = array[index1];
    array[index1] = array[index2];
    array[index2] = tmp;
}

void shift(struct process *array, int source, int destination) {
    // Cycle shift right for the elements from destination to source
    if (source > 0 && source > destination) {
        // Shift elements from the left of source index up to destination to the right
        struct process tmp;
        tmp = array[source];
        for (unsigned int i = source; i > destination; i--) {
            array[i] = array[i-1];
        }
        // Put the element from source to the destination index
        array[destination] = tmp;
    }
}

void sort(struct process *values, int length) {
    // Bubble sort for processes array, sorting by index
    if (length > 1) {
        for (unsigned int i = length - 1; i > 0; i--) {
            for (unsigned int j = 0; j < i; j++) {
                if (values[j].index > values[j+1].index) {
                    swap(values, j, j+1);
                }
            }
        }
    }
}

int main() {
    int count, quantum;
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
        struct process tmp = {i+1, arrival, service, -1, service, -1};
        processes[i] = tmp;
    }
    
    printf("Enter the quantum duration: ");
    scanf("%d", &quantum);
    
    int time = 0, processes_finished = 0, spent_time;
    while (processes_finished < count) {
        for (unsigned int j = processes_finished; j < count; j++) {
            if (processes[j].arrival <= time && processes[j].remaining > 0) {
                // Schedule the processes that are ready to be executed and not yet finished
                if (processes[j].started == -1)
                    processes[j].started = time;
                spent_time = quantum < processes[j].remaining ? quantum : processes[j].remaining;
                processes[j].remaining -= spent_time;
                time += spent_time;
                
                // Don't consider the process anymore if it's finished
                if (processes[j].remaining == 0) {
                    processes[j].exit = time;
                    
                    /*  
                     *  This is needed to preserve the index order of the processes.
                     *  Might use swap() and sort() instead; or just swap() and have another result
                     *  (but the same ET for the last process) — left the commented code below
                     */
                    shift(processes, j, processes_finished);
                    processes_finished++;
                    
                    // swap(processes, j, processes_finished);
                    // processes_finished++;
                    // sort(processes + processes_finished, count - processes_finished);
                }
            }
        }
    }
    
    float sumTAT = 0, sumWT = 0;
    printf("The processes:\n");
    printf("P#:\tAT:\tBT:\tCT:\tTAT:\tWT:\n");
    for (unsigned int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            processes[i].index, processes[i].arrival, processes[i].service,      // P#, AT, BT
            processes[i].exit,                                                   // CT (it's actually ET!)
            processes[i].exit - processes[i].arrival,                            // TAT
            processes[i].exit - processes[i].arrival - processes[i].service);    // WT
        sumTAT += processes[i].exit - processes[i].arrival;
        sumWT  += processes[i].exit - processes[i].arrival - processes[i].service;
    }
    printf("\nAverage TAT: %f\n", sumTAT / count);
    printf("Average WT: %f\n", sumWT / count);
    
    free(processes);
    return 0;
}