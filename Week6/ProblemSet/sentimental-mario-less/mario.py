# TODO
#Importing libraries

## Collecting the user input for the height of the pyramid

while True:
    try:
        height = int(input("Height: "))
        if (height >= 1) and (height <= 8):
            break
    except:
        print("", end="")

# prints newline
for i in range(height):
    # This prints empty spaces
    # The formulae height - i - 1 gives you:
    # 3 spaces when i = 0,
    # 2 spaces when i = 1,
    # 1 space when i = 2,
    # 0 space when i = 4
    for j in range(height-i-1):
        print(" ",end="")
    # after printing the appropriate number of empty spaces, the program will create print # values accordingly
    # you will need to have i + 1 because of the zero indexing that python starts of with
    # prints hashes accordingly
    for i in range(i+1):
        print("#", end="")
    print()



















































