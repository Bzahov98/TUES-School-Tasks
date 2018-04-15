#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *print_hello(void *data)
{
    size_t thread_num = (size_t)data;

    printf("Hello world! It's me - thread %zd\n", thread_num);

    return 0;
}

int main()
{
    size_t i;
    pthread_t threads[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++) {
        printf("Creating thread %zd..\n", i);
        int error = pthread_create(&threads[i], NULL, print_hello, (void*)i);
        if (error != 0) {
            fprintf(stderr, "Error creating thread %zd: error: %d\n", i, error);
        }
    }

    pthread_exit(NULL);
    return 0;
}
