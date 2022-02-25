#include <stdio.h>
#include <string.h>
#include <math.h>

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
        struct NumInfo *temp = (struct node *)malloc(sizeof(struct NumInfo));
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
            struct NumInfo *temp = (struct node *)malloc(sizeof(struct NumInfo));
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

void QRootList(int N)
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

double QRoot()
{
    struct NumInfo *trav = head;
    double RSum = 0;
    while (trav != NULL)
    {
        RSum += pow(trav->num, ((double)trav->occ / 4));
        trav = trav->next;
    }
    return RSum;
}

int main()
{
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

    printf("First number is: %d\n", m);
    printf("Second number is: %d\n", n);
    return 0;
}