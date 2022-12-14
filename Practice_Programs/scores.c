#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = get_float("How many scores? ");
    // Dumb way of getting three integers
    // int score1 = 72;
    // int score2 = 73;
    // int score3 = 33;
    int score[n];
    // creating a for loop to get 3 integers from the user
    for (int i =0; i < n ; i++)
    {
        score[i] = get_float("Number please! ");
    }
    // // This throws you an error because all three scores / 3 will return
    // a floating point value
    // printf("Average: %f\n", (score1+score2+score3) / 3);
    // To resolve the above error, you have to change divide 3 -> 3.0
    // This will tell C that the default value is now a floating point value


    printf("Average is... %d\n", (score[0] + score[1] + score[2]) / n );

}