
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 3

size_t result = 0;
pthread_mutex_t result_mutex;

void *busy_work(void *data)
{
    int i;
    size_t thread_num = (size_t)data;

    printf("Hello world! It's me - thread %zd\n", thread_num);

    for (i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&result_mutex);
        result++;
        pthread_mutex_unlock(&result_mutex);
    }
    
    pthread_exit(NULL);
}

int main()
{
    size_t i;
    pthread_t threads[NUM_THREADS];

	pthread_mutex_init(&result_mutex, NULL);

    for (i = 0; i < NUM_THREADS; i++) {
        printf("Creating thread %zd..\n", i);
        int error = pthread_create(&threads[i], NULL, busy_work, (void*)i);
        if (error != 0) {
            fprintf(stderr, "Error creating thread %zd: error: %d\n", i, error);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        printf("Waiting for thread %ld to finish..\n", i);
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "Error joining thread %zd: error: %d\n", i, error);
        }
    }

	printf("Result: %zd\n", result);

	pthread_mutex_destroy(&result_mutex);
    pthread_exit(NULL);
    return 0;
}
