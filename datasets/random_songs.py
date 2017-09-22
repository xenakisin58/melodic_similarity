from random import randint

f = open("lakh_corr_unique_midi.dat","r")
content = f.readlines()
output = []
num_titles_needed = 7
i = 0
while i < num_titles_needed:
    temp = content[randint(0,1110)]
    if temp not in output:
        output.append(temp)
        i+=1
    else:
#        print str(temp.split("|")[0])," already in output"
        continue

for entry in output:
    print entry,
