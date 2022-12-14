# TODO

#Importing the libraries
from cs50 import get_int, get_string

while True:
    try:
        card = get_int("Number: ")
        if card > 0:
            break
    except:
        print("Error")

## Checking based on Luhn's algorithm
def luhn_checker(card):
    ## Creating a function to turn card number into a list of number
    def digits_of(n):
        ## Turning the card number into a list of number
        return[int(i) for i in str(n)]
    ## Creating a variable to store the list of card numbers
    digits = digits_of(card)
    ## Creating a variable to store all odd numbers starting from the back of the number
    odd_number = digits[-1::-2]
    ## Creating a variable to store all even numbers starting from the back of the number
    even_number = digits[-2::-2]
    ## Creating a count variable
    count = 0
    ## Odd digits are to be summed up together
    count += sum(odd_number)
    ## Even digits have to be multiplied by 2 and added together
    for i in (even_number):
        count += sum(digits_of(i*2))

    ## Checking that the second last number is equal to 0
    return count %10

length = 0
visa = card
master = card
amex = card

length = len(str(card))
##Visa criteria:
#if number of digits == 13 or number of digits == 16 AND number starts with 4

while visa >=10:
    visa = int(visa/10)

## Amex Criteria:
 # if number of digits == 15 AND number starts with 34 or 37

while amex >= 10**13:
    amex = int(amex/10**13)

## Master criteria:
 # if number of digits == 16 AND number starts with 51,52,53,54 or 55

while master >= 10**14:
    master = int(master/10**14)


## Sorting algorithm
if luhn_checker(card) == 0:
    if visa == 4 and (length == 13 or length == 16):
        print("VISA")
    elif length == 15 and (amex == 34 or amex ==37):
        print("AMEX")
    elif length == 16 and ( 51 <= master <= 55):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")
