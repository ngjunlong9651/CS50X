# TODO
# Importing libraries

from cs50 import get_float

## Checking that the user only inputs non negative amounts
while True:
    try:
        amount = get_float("Change owed :")
        if amount >0:
            break
    except:
        print("Error")

cents= amount*100

count_of_coins = 0

while cents >= 25:
    cents -= 25
    count_of_coins += 1

while cents >= 10:
    cents -= 10
    count_of_coins += 1

while cents >= 5:
    cents -= 5
    count_of_coins +=1

while cents >= 1:
    cents -=1
    count_of_coins += 1

print("Total coins: ", count_of_coins)
