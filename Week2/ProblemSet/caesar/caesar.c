#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    if (argc!=2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i ++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key \n");
            return 1;
        }
    }
    // Convert user input into an integer for ASCII manipulation
    int key = atoi(argv[1]);
    string ptext = get_string("plaintext: ");
    printf("ciphertext: ");
    for(int i=0; i<strlen(ptext); i++)
    {
        if(isupper(ptext[i]))
        {
            printf("%c", (((ptext[i] - 65) + key) %26) + 65);
        }
        else if (islower(ptext[i]))
        {
            printf("%c", (((ptext[i] - 97) + key) % 26) + 97);
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
}