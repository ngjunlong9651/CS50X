#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get card number
    long cardn = get_long("Number: ");
    // Count length
    int length = 0;
    long creditcard = cardn;
    while (creditcard > 0)
    {
        creditcard = creditcard / 10;
        length++;
    }
        // Check if length is valid
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }
        // Calculate
    int sum1 = 0;
    int sum2 = 0;
    long x = cardn;
    int total = 0;
    int mod1;
    int mod2;
    int d1;
    int d2;
    do
    {
        // Remove last digit and add to sum1
        mod1 = x % 10;
        x = x / 10;
        sum1 = sum1 + mod1;
        // Remove second last digit
        mod2 = x % 10;
        x = x / 10;
        // Double second last digit and add digits to sum2
        mod2 = mod2 * 2;
        d1 = mod2 % 10;
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;
    }
    while (x > 0);
    total = sum1 + sum2;

    // Next check Luhn Algorithm
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
        // Get starting digits
    long start = cardn;
    do
    {
        start = start / 10;
    }
    while (start > 100);
        // Next check starting digits for card type
    if ((start / 10 == 5) && (0 < start % 10 && start % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
        else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))
    {
        printf("AMEX\n");
    }
        else if (start / 10 == 4)
    {
        printf("VISA\n");
    }
        else
    {
        printf("INVALID\n");
    }

// Hard Code
    // // Code to get user to input their credit card details:
    // long card;
    // do
    // {
    //     card = get_long("What is your card number? ");
    // }
    // //ensuring that the card number given is more than 0
    // while (card < 0);

    // // Getting the correct digit for Luhn's algo
    // int card1, card2, card3, card4, card5, card6, card7, card8;
    // card1 = (((card % 100)/10)*2);
    // card2 = (((card % 10000)/1000)*2);
    // card3 = (((card % 1000000)/10000)*2);
    // card4 = (((card % 100000000)/10000000)*2);
    // card5 = (((card % 10000000000)/1000000000)*2);
    // card6 = (((card % 1000000000000)/100000000000)*2);
    // card7 = (((card % 100000000000000)/10000000000000)*2);
    // card8 = (((card % 10000000000000000)/1000000000000000)*2);

    // card1 = (card1%100/10) + (card1%10);
    // card2 = (card2%100/10) + (card2%10);
    // card3 = (card3%100/10) + (card3%10);
    // card4 = (card4%100/10) + (card4%10);
    // card5 = (card5%100/10) + (card5%10);
    // card6 = (card6%100/10) + (card6%10);
    // card7 = (card7%100/10) + (card7%10);
    // card8 = (card8%100/10) + (card8%10);

    // int sum1 = card1 + card2 + card3 + card4 + card5 + card6 + card7 + card8;

    // // finding the digits that were not multiplied by 2
    // int card9, card10, card11, card12, card13, card14, card15, card16;
    // card9 = (card % 10);
    // card10 = (card % 1000/100);
    // card11 = (card % 100000/10000);
    // card12 = (card % 10000000/1000000);
    // card13 = (card % 1000000000/100000000);
    // card14 = (card % 100000000000/10000000000);
    // card15 = (card % 10000000000000/1000000000000);
    // card16 = (card % 1000000000000000/100000000000000);

    // int sum2 = card9 + card10 + card11 + card12 + card13 + card14 + card15 + card16;
    // int sum3 = sum1 + sum2;

    // // Determining if card number is valid

    // if ((sum3%10)!=0)
    // {
    //     printf("%s \n","Invalid Card Number! ");
    //     return 0;

    // }
    // // Determining type of card, first need to declare length of card
    // int length = 0;
    // long visa = card;
    // long amex = card;
    // long master = card;

    // // Determining the length of the card, for every 1 digit which is presented by
    // // total length of card divide by 10, length of card ++. Every 1 digit, length
    // // is increased by 1. Hence, effectively counting the length of card numbers.
    //     while (card > 0)
    // {
    //     card = card/10;
    //     length++;
    // }


    // // Determining Visa Card
    // while (visa >= 10)
    // {
    //     visa /= 10;

    // }
    // if (visa == 4 && (length == 13 || length == 16))
    // {
    //     printf("%s \n","VISA");
    //     return 0; // so that program will stop running
    // }

    // // Determining Amex Card
    // while (amex >= 10000000000000)
    // {
    //     amex /=10;
    // }
    // if (length == 15 && (amex == 34 || amex ==37))
    // {
    //     printf("%s\n","AMEX");
    //     return 0;
    // }

    // // Determining Master Card
    // while (master >= 100000000000000)
    // {
    //     master /= 100000000000000;
    // }
    // if (length == 16 && (master == 51 || master == 52 || master == 53 || master == 54 || master ==5))
    // {
    //     printf("%s\n","MASTERCARD");
    //     return 0;
    // }
    // else
    // printf("%s \n","INVALID");
    // return 0;

}