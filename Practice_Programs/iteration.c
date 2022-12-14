#include <cs50.h>
#include <stdio.h>

// Calling the draw function
void draw(int n);

int main(void)
{   //Getting height of the pyramid
    int height = get_int("What is the height: ");

    // Calling the draw function
    draw(height);
}

// Creating the draw function
void draw(int n)
{
    for (int i =0; i < n; i++)
    {
        for (int j =0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }

}