#include <cs50.h>
#include <stdio.h>
#include <string.h>


typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];
    people[0].name ="Carter";
    people[0].number = "96517120";

    people[1].name ="JL";
    people[1].number="96516120";

    for (int i = 0; i <2; i++)
    {
        if (strcmp(people[i].name,"Ashley") == 0)
        {
            printf("Found! %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not Found!\n");
    return 1;
}