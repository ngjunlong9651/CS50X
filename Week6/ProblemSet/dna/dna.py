import csv
import sys

## Importing library to take into account for CLA
from sys import argv

## Importing the csv library
import csv


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage python dna.py data.csv sequence.txt")
        sys.exit(1)


    # TODO: Read database file into a variable
    # Also need to manipulate the data to ensure that it is a list for easier comparison
    # The user will input the database as the first arguement
    with open(argv[1]) as e:
        reader = csv.DictReader(e)
        dna_database = list(reader)


    # TODO: Read DNA sequence file into a variable
    ## The user will input the sequences as the second command line arguement
    with open(argv[2]) as f:
        dna_sequence = f.read()

    ## Create a dictionary to hold all the matches from sequences and databases
    matches = {}

    # TODO: Find longest match of each STR in DNA sequence
    for i in dna_database[0]:
        ## Creating keys within the matches dictionary based
        matches[i] = longest_match(dna_sequence, i)


    # TODO: Check database for matching profiles
    # Counter starts at 1 because there index 0 is the name, hence no need to compare index 0
    suspect = "No Match"
    suspect_counter = 1
    ## The code below will loop through the length of the database
    for i in range(len(dna_database)):
        ## The code below loops through each element in matches
        for j in matches:
            ## Converts the element in matches to string
            ## Compares each element of matches against each element of each row in dna database
            if str(matches[j]) == dna_database[i][j]:
                ## if both matches[i] == dna_database[i][j], suspect counter increases. This checks through each STR
                suspect_counter += 1
                ## If suspect counter equals the length of matches of STRs. We can identify that this DNA sequence belongs to the suspect
        if suspect_counter == len(matches):
            suspect = dna_database[i]["name"]
            break
        else:
            suspect_counter = 1
    print(suspect)

    return

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
