#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;
int th_count = 0;
double qSum = 0;

struct NumInfo
{
    int num;
    int occ;
    struct NumInfo *next;
};

struct NumInfo *head = NULL;
struct NumInfo *tail = NULL;

struct NumInfo *factorPresent(int F)
{
    int found = 0;
    struct NumInfo *trav = head;
    while (trav != NULL)
    {
        if (trav->num == F)
        {
            found = 1;
            break;
        }
        trav = trav->next;
    }
    return trav;
}

void appendFactors(int F)
{
    if (head == NULL && tail == NULL)
    {
        struct NumInfo *temp = (struct NumInfo *)malloc(sizeof(struct NumInfo));
        temp->num = F;
        temp->occ = 1;
        temp->next = NULL;
        head = temp;
        tail = temp;
    }
    else
    {
        if (factorPresent(F) == NULL)
        {
            struct NumInfo *temp = (struct NumInfo *)malloc(sizeof(struct NumInfo));
            temp->num = F;
            temp->occ = 1;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
        }
        else
        {
            struct NumInfo *ptr = factorPresent(F);
            ptr->occ += 1;
        }
    }
}

int isPrime(int N)
{
    int primeStatus = 1;
    for (int i = 2; i < N / 2; i++)
    {
        if (N % i == 0)
            primeStatus = 0;
    }
    return primeStatus;
}

double QRootList(int N)
{
    int i;
    while (!isPrime(N))
    {
        for (i = 2; i < N / 2; i++)
        {
            if (N % i == 0)
            {
                appendFactors(i);
                break;
            }
        }
        N = N / i;
    }
    appendFactors(N);

    struct NumInfo *trav = head;
    double RSum = 1;
    while (trav != NULL)
    {
        RSum *= pow(trav->num, ((double)trav->occ / 4));
        trav = trav->next;
    }
    return RSum;
}

void deleteList()
{
    struct NumInfo *current = head;
    struct NumInfo *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

void printList()
{
    printf("\nPrinting factors list.. \n");
    struct NumInfo *trav = head;
    while (trav != NULL)
    {
        printf("Factor is: %d\n", trav->num);
        printf("It occured %d\n", trav->occ, " times.");
        trav = trav->next;
    }
}

double qRoot(int N)
{
    double sroot = sqrt(N);
    double qroot = sqrt(sroot);
    return qroot;
}

void *intervalSum(void *args)
{
    int *interval_array = (int *)args;
    int s = interval_array[0];
    int e = interval_array[1];
    printf("Value of s is: %d\n", s);
    printf("Value of e is: %d\n", e);
    int i;
    double sum = 0;
    for (i = s; i <= e; i++)
    {
        double qroot = qRoot(i);
        printf("Qroot is: %f\n", qroot);
        sum += qroot;
    }
    printf("Sum of interval %d -> %d is: %f\n", s, e, sum);
    sem_wait(&semaphore);
    qSum += sum;
    sem_post(&semaphore);
    return NULL;
}

void makeIntervals(int m, int n)
{
    int i, start = 1;
    int end = (int)(n / m);
    for (i = 0; i <= m; i++)
    {
        int intervalArray[2];
        pthread_t i;
        intervalArray[0] = start;
        intervalArray[1] = end;
        pthread_create(&i, NULL, &intervalSum, &intervalArray);
        pthread_join(i, NULL);
        start = (end + 1);
        end = end + (int)(n / m);
    }
}

int main()
{
    sem_init(&semaphore, 0, 1);
    char uInput[20];
    printf("Enter numbers: ");
    fgets(uInput, sizeof(uInput), stdin);
    printf("Numbers entered are: ");
    puts(uInput);

    int i = 0;
    char *array[2];
    char *chunk = strtok(uInput, " ");
    while (chunk != NULL)
    {
        array[i++] = chunk;
        chunk = strtok(NULL, " ");
    }

    int m = atoi(array[0]);
    int n = atoi(array[1]);

    th_count = m;
    printf("M is: %d\n", m);
    printf("N is: %d\n", n);

    makeIntervals(m, n);
    double qR = QRootList(n);
    printf("Qroot is: ", qR);
    // printf("QRoot is: %f\n", qR);
    return 0;
}