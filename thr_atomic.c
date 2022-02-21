#include <stdio.h>
#include <string.h>

struct NumInfo
{
    int num;
    int occ;
    struct NumInfo *next;
};

struct NumInfo *head = NULL;

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
    }
    return trav;
}

void appendFactors(int F)
{
    if (factorPresent(F) == NULL)
    {
        struct NumInfo *temp = (struct node *)malloc(sizeof(struct NumInfo));
        temp->num = F;
        temp->occ = 0;
        temp->next = NULL;
    }
    else
    {
        struct NumInfo *ptr = factorPresent(F);
        ptr->occ += 1;
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

double SRoot(int N)
{
    while (N != 1)
    {
        if (isPrime(N) == 1)
        {
            appendFactors(N);
        }
        else
        {
            for (int i = 0; i < N / 2; i++)
            {
                if (N % i == 0)
                {
                    appendFactors(N / i);
                }
            }
        }
    }
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