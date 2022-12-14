#include <cs50.h>
#include <stdio.h>

// int main(void)
// {
//     //Need a do while loop
//     int height;
//     int row;
//     int col;
//     int space;
//     do
//     {
//         // Getting the height of the wall for mario
//         height = get_int("What is the height of the obstacle? \n");
//     }
//     while (height < 1 || height > 8);
//     // As long as row(counter) is less than height print a new line
//     for (row = 0; row < height; row++)
//     {
//         // transforming it into a right aligned pyramid
//         // for (space = 0; space<height - row - 1; space++)
//         // {
//         //     printf(" ");
//         // }
//         // Creating the #
//         for (col=0; col <= row; col++)
//         {
//         printf("#");
//         }
//     printf("\n");
//     }
// }



int main(void)
{
    int height;
    do
    {
        height = get_int("Please enter a height between 1 and 8 ");
    }
    while (height <1 || height >8);
    //Creating the desired amount of rows
        for (int row = 0; row < height; row++)
        // printf("- \n");
        {
            // space
            for (int space = 0; space < height - row - 1; space++)
            {
                printf(" ");
            }
                // creating a nested for loop to create the hashtags
                // for every row, col will be initialised at zero, as long as col is less than or equal to row, every iteration, col will print out a
                // # till it is equal to the row counter.
                for (int col = 0; col <= row; col++)
                {
                printf("#");
                }
        printf("  ");
        for (int col = 0; col <=row; col++)
        {
            printf("#");
        }
        printf("\n");
        }
}