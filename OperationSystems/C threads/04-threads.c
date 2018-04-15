#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 3

size_t result = 0;
size_t result_lock = 0;

void *busy_work(void *data)
{
    int i = 0;
    size_t thread_num = (size_t)data;

    printf("Hello world! It's me - thread %zd\n", thread_num);

    while (i < 1000000)
    {
		// not portable accross compilers (should work on GCC 4.1+) and 
		// architectures (should work on modern x86 compatible processors)
		size_t prev = __sync_lock_test_and_set(&result_lock, 1);
		if (prev == 0)
		{
			result++;
			__sync_lock_release(&result_lock);
			i++;
		}
    }
    
    pthread_exit(NULL);
}

int main()
{
    size_t i;
    pthread_t threads[NUM_THREADS];

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

    pthread_exit(NULL);
    return 0;
}
