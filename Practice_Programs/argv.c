#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // if user types one word, it will trigger
    if (argc ==2)
    {
        printf("hello, %s\n", argv[1]);

    }
    else
    // if user types more than one word or less than one word
    {
        printf("Hello World\n");
    }
}