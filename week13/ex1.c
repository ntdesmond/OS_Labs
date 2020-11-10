// Ex. 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int can_finish(int* allocated, int* requested, int* available, int resource_types) {
    //   Process can't proceed only if it doesn't have all the requested resources
    // even if it is given all the available ones
    for (int i = 0; i < resource_types; i++) {
        if (allocated[i] + available[i] < requested[i])
            return 0;
    }
    return 1;
}

void finish(int* allocated, int* available, int resource_types) {
    for (int i = 0; i < resource_types; i++) {
        available[i] += allocated[i];
        allocated[i] = 0;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf(
            "Usage: %s <input filename> <resource types> <processes> <output filename>; e.g. %s in.txt 3 5 out.txt\n",
            argv[0], argv[0]
        );
        return 1;
    }
    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    int resource_types = atoi(argv[2]), processes = atoi(argv[3]);
    int *existing  = (int*)malloc(resource_types * sizeof(int));
    int *available = (int*)malloc(resource_types * sizeof(int));
    int *allocated = (int*)malloc(resource_types * processes * sizeof(int));
    int *requested = (int*)malloc(resource_types * processes * sizeof(int));

    for (int i = 0; i < resource_types; i++) {
        fscanf(input, "%d", &existing[i]);
    }
    for (int i = 0; i < resource_types; i++) {
        fscanf(input, "%d", &available[i]);
    }
    for (int i = 0; i < processes * resource_types; i++) {
        fscanf(input, "%d", &allocated[i]);
    }
    for (int i = 0; i < processes * resource_types; i++) {
        fscanf(input, "%d", &requested[i]);
    }
    fclose(input);

    char *finished = (char*)malloc(processes * sizeof(char));
    for (int i = 0; i < processes; i++) {
        finished[i] = 0;
    }

    int locked_count = processes;
    char deadlock;
    do {
        deadlock = 1;
        for (int i = 0; i < processes; i++) {
            if (!finished[i] && can_finish(allocated + i * resource_types, requested + i * resource_types, available, resource_types)) {
                finish(allocated + i * resource_types, available, resource_types);
                finished[i] = 1;
                locked_count--;
                deadlock = 0;
                printf("Process %d has got enough resources\n", i);
            }
        }
    } while (!deadlock && locked_count > 0);

    FILE* output = fopen(argv[4], "w");
    if (output == NULL) {
        printf("Error opening file %s\n", argv[4]);
        return 1;
    }
    if (locked_count > 0)
    	fprintf(output, "%d processes are deadlocked\n", locked_count);
    else
    	fprintf(output, "No deadlock detected\n");
    fclose(output);

    printf("Wrote the result to %s\n", argv[4]);
    free(finished);
    free(existing);
    free(available);
    free(allocated);
    free(requested);
    return 0;
}
