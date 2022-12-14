//Including relevant packages
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i =0; i < candidate_count; i++)
    {
        if(strcmp(name,candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // This loop counts for the votes for each session within the election
    // If the candidate was eleminated, it skips to the next preference by the voter
    for(int i=0; i < candidate_count; i++)
    {
        for (int j=0; j < candidate_count; j++)
        {
            int h = preferences[i][j];
            if (candidates[i].eliminated == false)
            {
                candidates[i].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    // To check if any individual candidates has more than 50% of the total number of votes
    for (int i =0; i <candidate_count; i++)
    {
        if(candidates[i].votes > (voter_count)/2)
        {
            printf("%s\n",candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    // Basically need to find the candidate with the least number of vote that is still within the election
    // Creating a variable to be used as the smallest number of votes
    int count_of_votes = voter_count;
    // Parsing through the list of candidates with a counter
    for (int i =0; i < candidate_count; i++)
    {
        // Creating the algo for replacing the least number of votes variable
        if(candidates[i].votes < count_of_votes && candidates[i].eliminated == false)
        {
            // Replacing
            count_of_votes = candidates[i].votes;
        }
    }
    return count_of_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // If the number of votes between all remaining candidates are the same
    // Return a tie result only if perfect tie
    int tiecount = 0;
    int onrun = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        // During that election instance add to both counter if the candidate has the least amount of vote and is not eliminated
        if(candidates[i].eliminated == false && candidates[i].votes == min)
        {
            // Count for number of times the program returns a tie
            tiecount++;
            // On Run stands for still in the running
            onrun++;
        }
        // During that election if no tie
        else if (candidates[i].eliminated == false)
        {
            onrun++;
        }
    }

    // Checking for tie

    if (tiecount == onrun)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    // Create a simple iteration eliminating those with the min votes
    for (int i =0; i <candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
