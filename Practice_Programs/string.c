#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = get_string("What is your name? ");
    printf("Output ");
    // int length = strlen(name);
    for (int i = 0, length = strlen(name); i < length; i++)
    {
        printf("%c",name[i]);
    }
    printf("\n");
}