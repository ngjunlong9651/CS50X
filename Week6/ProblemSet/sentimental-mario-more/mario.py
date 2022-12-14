# TODO
#Importing libraries

## Collecting the user input for the height of the pyramid
while True:
    try:
        height = int(input("Height? "))
        if height > 0  and height < 9:
            break
    except:
        print("", end="")

# prints newline
for i in range(0,height,1):
    ## Extending the limit of range by 3
    for j in range(0,height+i+3,1):
        if(j==height or j == height+1 or i+j <height-1):
            print(" ",end="")
        else:
            print("#",end="")
    print() 
