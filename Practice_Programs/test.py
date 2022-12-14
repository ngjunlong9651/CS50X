tuple1 = (1, 2, [1], [1, 2])
dict1 = {
'a': [1],
'b': [2],
}
for i in dict1:
    if dict1[i] in tuple1:
        dict1[i] = 'hit'
print(dict1)