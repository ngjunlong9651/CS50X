#include <stdio.h>
#include<stdlib.h>

// Old school way of getting user input

int main(void)
{
    // Old school way of getting integer from user
    //int x;
    //printf("x:");
    //scanf("%i", &x);// another function in stdio.h telling C where to put where the user put input
    //printf("x: %i\n",x);

    //Old school way of getting strings from user
    char *s = malloc(4);
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
}