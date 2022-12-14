# TODO

from cs50 import get_int, get_string

user_text = get_string("Text: ")

## Declaring variables for words, sentence and letters

letters = 0
words = 1
sentence = 0

for i in user_text:
    if i.isalpha():
        letters += 1
    elif i == " ":
        words +=1
    elif i =="!" or i== "?" or i ==".":
        sentence += 1

## Using the formula:
coleman_index = 0.0588 * (letters/words * 100) - 0.296 * (sentence/words * 100) - 15.8
if coleman_index < 1:
    print("Before Grade 1")
elif coleman_index >= 16:
    print("Grade 16+")
else:
    print("Grade ", round(coleman_index))

