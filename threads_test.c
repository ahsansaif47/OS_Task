#include <stdio.h>
#include <pthread.h>

void *sample()
{
    printf("Threads sample..\n");
}

void *intervalSum(void *args)
{
    int *interval_array = (int *)args;
    int s = interval_array[0];
    int e = interval_array[1];

    int i;
    double sum = 0;
    for (i = s; i <= e; i++)
        sum += i;

    printf("Total sum: %f", sum);
    return NULL;
}

int main()
{
    pthread_t tid;
    int array[2] = {5, 10};
    pthread_create(&tid, NULL, &intervalSum, &array);
    pthread_join(tid, NULL);
    return 0;
}