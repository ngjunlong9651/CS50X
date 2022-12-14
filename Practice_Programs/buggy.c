#include <stdio.h>
#include <cs50.h>

// Demonstrating Step-In Debug

int get_negative_int(void);

int main(void)
{
   int i = get_negative_int();
   printf("%i\n",i);

}


// Creating a function called get_negative_int
int get_negative_int(void)
{
    int n;
    do
    {
        n = get_int("Enter a negative integer: ");
    }
    // for it to be buggy, you have to switch the > to <
    while (n > 0);
    return n;
     
}