#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    // Counting how many candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i =0; i < candidate_count; i++)
    {
        // Counting the votes from Command Line Arguement
        // If user input matches the name from candidates.name then that specific candidate will add 1 to their total vote count
        if (strcmp(candidates[i].name,name)==0)
        {
            candidates[i].votes ++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int max_vote = 0;
    //Determine highest number of vote
    for(int i =0; i < candidate_count; i++)
    {
        // If the specific candidate has more vote, his number of votes shall be replace max_vote.
        if (candidates[i].votes  > max_vote )
        {
            // This will store the index of the highest votes per candidate
            max_vote = candidates[i].votes;
        }
    }
        // Identify and print the winner
        for (int i = 0; i <candidate_count; i++)
    {
        // Determining the index with the highest vote
        if(max_vote == candidates[i].votes)
        {
            //Using the same index of the highest vote to access the candidate with the highest vote
            printf("The winner is: %s\n",candidates[i].name);
        }
    }
    return;


}