#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string names[] = { "Bill","George","Dick","Johnny","Percy","Ron","Ginny"};
    for (int i =0; i <7; i++)
    {
        // strcmp returns 0 if both strings are equal to each other
        if (strcmp(names[i],"Ron") == 0)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not Found!\n");
    return 1;
}