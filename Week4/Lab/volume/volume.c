// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t SAMPLE_SOUND;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    // If user failed to produce four inputs, program returns error message and exit code 1
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO:
    // Copy header from input file to output file
    // Creating an array to store header
    uint8_t header_buffer[44];
    // Reading from the input file, using the fread function which takes in four arguements
    fread(header_buffer,sizeof(uint8_t),44,input);
    // Writing to the output file, using the fwrite function which takes in four arguements
    fwrite(header_buffer, sizeof(uint8_t),44,output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t sample_buffer;
    while(fread(&sample_buffer, sizeof(int16_t),1,input))
    {
        sample_buffer *= factor;
        fwrite(&sample_buffer,sizeof(int16_t),1,output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
