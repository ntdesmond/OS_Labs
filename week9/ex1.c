// Ex. 1
// Hit/miss ratios:
// 10  frames: 0.009082 (9 hits)
// 50  frames: 0.053741 (51 hit)
// 100 frames: 0.102536 (93 hits)
#include <stdio.h>
#include <stdlib.h>
#define BIT_WIDTH 32

int index_by_page(int* frames, int page_number, int frame_count) {
    // Returns the index of the page in the memory or -1 if no page present
    for (int i = 0; i < frame_count; i++) {
        if (frames[i] == page_number)
            return i;
    }
    return -1;
}

int least_referenced(int* counters, int frame_count) {
    // Returns the index of the page with the lowest aging counter
    int min = counters[0], index = 0;
    for (int i = 1; i < frame_count; i++) {
        if (counters[i] < min) {
            min = counters[i];
            index = i;
        }
    }
    return index;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("You must specify the number of page frames! e.g. ./ex1 50\n");
        return 0;
    }
    FILE* test_file = fopen("ex1.txt", "r");
    if (test_file == NULL) {
        printf("Error opening test file ex1.txt\n");
        return 0;
    }

    int frame_count = atoi(argv[1]);
    int *page_numbers = malloc(frame_count * sizeof(int));
    int *counters = malloc(frame_count * sizeof(int));
    int current_page, used = 0, hit_count = 0, miss_count = 0;
    while (fscanf(test_file, "%d", &current_page) != EOF) {
        // Search for the page in the memory
        int index = index_by_page(page_numbers, current_page, used);
        if (index == -1) {
            // New position is either empty frame in memory or the one referenced long ago
            int new_pos = used < frame_count ? used++ : least_referenced(counters, frame_count);
            page_numbers[new_pos] = current_page;
            counters[new_pos] = 1 << (BIT_WIDTH - 1);
            miss_count++;
        }
        else {
            for (int i = 0; i < used; i++) {
                // Shift counter right
                counters[i] >>= 1;
                // Set MSB to 1 if the page was referenced, 0 otherwise
                counters[i] &= (i == index ? 1 : 0) << (BIT_WIDTH - 1);
            }
            hit_count++;
        }
    }
    printf("Hit count: %d\nMiss count: %d\nHit/Miss ratio: %f\n", hit_count, miss_count, (double)hit_count / miss_count);
    free(page_numbers);
    free(counters);
    return 0;
}
