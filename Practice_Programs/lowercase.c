#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// Manually making it lower case
// int main(void)
// {
//     string s = get_string("Original: ");
//     printf("Edited: ");
//     for (int i =0, n = strlen(s); i < n; i++)
//     {
//         if (s[i] >= 'A' && s[i] <= 'Z')
//         {
//             printf("%c", s[i]+32);
//         }
//         else
//         {
//             printf("%c",s[i]);
//         }
//     }
//     printf("\n");
// }

//Using islower
int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isupper(s[i]))
        {
            printf("%c", tolower(s[i]));
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
