#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    // Dynamically allocate an array of size 3
    int *list = malloc(3*sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;


    // Time passes
    // Allocating new array of size 4
    int *tmp = realloc(list, 4*sizeof(int));
    // The issue is that the new spot containing 4 will be randomly assigned to another spot in the memory
    // Basically pointing to another chunk of memory

    // To fix this issue, need to do the following
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }
    // Copy size of old array into size of new array
    for (int i =0; i < 3; i ++)
    {
        tmp[i] = list[i];
    }
    // Add a new element into the array
        tmp[3] = 4;
        list = tmp;

        // Printing new array
        for (int i =0; i <4; i ++)
        {
            printf("%i\n",list[i]);
        }
        free(list);
        return 0;
}
