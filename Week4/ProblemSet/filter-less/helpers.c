#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through every pixel row
    for (int i =0; i < height; i++)
    {
        // Iterating through every pixel column
        for (int j =0; j< width; j++)
        {
            // Convert pixels to float
            float ConvertRed = image[i][j].rgbtRed;
            float ConvertBlue = image[i][j].rgbtBlue;
            float ConvertGreen = image[i][j].rgbtGreen;

            // Finding average value
            int ConvertAverage = round((ConvertRed + ConvertGreen + ConvertBlue)/3);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = ConvertAverage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through every pixel row
    for (int i=0; i < height; i++)
    {
        // Iterating through each column
        for(int j =0; j <width; j++)
        {
            // Converting all pixels in image to float value
            float(originalRed) = image[i][j].rgbtRed;
            float(originalBlue) = image[i][j].rgbtBlue;
            float(originalGreen) = image[i][j].rgbtGreen;

            // Using the formula provided to get new value for each of the pixel
            int(sepiaRed) = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int(sepiaGreen) = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int(sepiaBlue) = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Working around the constraint of 255
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Updating final pixel value
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i =0; i<height; i++)
    {
        for (int j =0; j < (width/2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j+1)];
            image[i][width - (j+1)] = temp;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating a copy of the image
    RGBTRIPLE temp[height][width];

    // Looping through all rows and the columns of the image
    for (int i =0; i < height; i ++)
    {
        for (int j = 0; j<width; j++)
        {
            // Saving into new temp variable
            temp[i][j] = image[i][j];

        }
    }


    for (int i =0; i < height; i ++)
    {
        for (int j =0; j<width; j++)
        {
            int totalRed, totalGreen, totalBlue;
            totalRed = totalBlue = totalGreen = 0;
            float counter =0.00;

            //Getting the neighboring pixels
            for (int x =-1; x <2; x++)
            {
                for (int y =-1; y<2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    // Checking if these pixels are within the grid and are valid
                    if (currentX < 0 || currentX > (height -1 ) || currentY <0 || currentY > (width-1))
                    {
                        continue;
                    }

                    // Getting the image value
                    totalRed += image[currentX][currentY].rgbtRed;
                    totalGreen += image[currentX][currentY].rgbtGreen;
                    totalBlue += image[currentX][currentY].rgbtBlue;

                    counter ++;
                }

                // Calculate average of neighboring pixels
                temp[i][j].rgbtRed = round(totalRed/counter);
                temp[i][j].rgbtBlue = round(totalBlue/counter);
                temp[i][j].rgbtGreen = round(totalGreen/counter);
            }

        }
    }

    //Copying the new pixels into the original image
    for (int i =0; i < height; i++)
    {
        for (int j=0; j<width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
