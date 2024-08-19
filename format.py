#This script takes the original diceware list and formats it such that a new word begins every 6 characters, padding empty characters with \0

f = open("diceware.wordlist.asc")
g = open("wd", "x")

words = f.readlines()[2:7778]

for line in words:
    word = line.split()[1]
    g.write(word)
    for i in range(6 - len(word)):
        g.write(" ")
