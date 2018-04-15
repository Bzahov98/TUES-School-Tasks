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
    
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    
    for (i = 0; i < NUM_THREADS; i++) {
        printf("Creating thread %zd..\n", i);
        int error = pthread_create(&threads[i], &thread_attr, print_hello, (void*)i);
        if (error != 0) {
            fprintf(stderr, "Error creating thread %zd: error: %d\n", i, error);
        }
    }
    
    pthread_attr_destroy(&thread_attr);
    
    pthread_exit(NULL);
    return 0;
}
