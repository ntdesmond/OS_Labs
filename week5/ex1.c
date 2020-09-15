#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int counter = 0;

void* print_thread_id(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();
    printf("This is a thread %d (id %ld)\n", counter, id);
    counter++;

    pthread_exit(NULL);
    return NULL;
}

int main(void)
{
    int n, err;
	pthread_t tid;
    
    printf("This is the main thread. Thread id is %ld\nEnter the amount of threads you want to create: ", pthread_self());
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        err = pthread_create(&tid, NULL, &print_thread_id, NULL);
        if (err != 0)
            printf("\ncan't create thread %d: [%s]", i, strerror(err));
		else
            printf("Thread %d (id %ld) created successfully\n", i, tid);
        pthread_join(tid, NULL); // this fixes the order of threads: block current until the created finishes
        // yet now the id is the same for all the threads since they are joined to the main one
    }
	while (counter < n); // loop to wait for threads to exit
	
    return 0;
}
