#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
// formula is index = 0.0588 * L - 0.296 * S - 15.8
// L is number of letters per 100 words
// S is average number of sentences per 100 words in text
    string user_sentence = get_string("Enter your sentence here: ");
    int word = 1;
    int sentence = 0;
    int letter = 0;
    for (int i=0; i < strlen(user_sentence); i++)
    {
        // Counting letters
        if ((user_sentence[i] >= 'A' && user_sentence[i] <= 'Z') || (user_sentence[i] >= 'a' && user_sentence[i]<='z'))
        {
            letter++;
        }
        // Couting sentences by . OR ! OR ?
        else if(user_sentence[i]=='.' || user_sentence[i]=='!' || user_sentence[i]=='?')
        {
            sentence++;
        }
        // Counting word by presence of space
        else if (user_sentence[i]==' ')
        {
            word++;
        }
    }
    printf("letters: %i; words: %i; sentences: %i\n", letter, word, sentence);
    // Building the scorer system
    int l_score = (float) letter/ (float) word * 100;
    int s_score = (float) sentence/ (float) word * 100;
    printf("L score: %i, S score: %i\n",l_score,s_score);
    // Adding the formula together
    float grade = (0.0588 * l_score) - (0.296 * s_score) - 15.8;
    printf ("Grade score: %f\n", grade);
    // Scoring system
    // Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.
    if (grade >=16)
    {//if above 16
        printf("Grade 16+\n");
    }
    else if (grade <=0)
    {// if below 0
        printf("Before Grade 1\n");
    }
    else if (grade > 0 && grade <16)
    {// if between 0 and 16
        printf("Grade %i\n", (int) round(grade));
    }

}