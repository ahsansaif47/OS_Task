#include <pthread.h>
#include <stdio.h>
#include <string.h>

struct NumInfo
{
    int num;
    int occ;
    struct NumInfo *next;
};

struct NumInfo *head = NULL;

int factorPresent(int F)
{
    int found = 0;
    struct NumInfo *trav = head;
    while (trav != NULL)
    {
        if (trav->num == F)
        {
            found = 1;
            trav->occ += 1;
            break;
        }
    }
    return found;
}

void appendFactors(int F)
{
    if (factorPresent(F) != 1)
    {
        struct NumInfo *temp = (struct node *)malloc(sizeof(struct NumInfo));
        temp->num = F;
        temp->occ = 0;
        temp->next = NULL;
    }
}

double squareRoot(int N)
{
    while (N != 1)
    {
        int i = 2;
        while (N % i != 0)
        {
            i++;
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