#include <stdio.h>
#include <pthread.h>
#include <math.h>

int array[3] = {2, 1, 3};

void *intervalSum(void *args)
{
    int *interval_array = (int *)args;
    // int n = sizeof(interval_array) / sizeof(interval_array[0]);
    // printf("Size of array is: %d", n);
    int i;
    double secondR = 0, qroot = 0, sum = 0;
    for (i = 0; i <= 2; i++)
    {
        // printf("Array value is: %d", interval_array[i]);
        secondR = sqrt(interval_array[i]);
        printf("Squareroot of %d is %f\n", interval_array[i], secondR);
        qroot = sqrt(secondR);
        printf("Quadroot of %d is %f\n", interval_array[i], qroot);
        sum += qroot;
    }
    printf("Total sum: %f", sum);
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, &intervalSum, &array);
    pthread_join(tid, NULL);
    return 0;
}