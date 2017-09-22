f = open('lakh_corr_dedupeEx_midi.dat','r')
content = f.readlines()
f.close
prev_title = curr_title = prev_line = curr_line = ""
count = 0
firstPass = 1

for line in content:
    prev_line = curr_line
    curr_line = line
    prev_title = curr_title
    curr_title = line.split(";")[1]
    if firstPass:
        print line,
        firstPass = 0
        continue
    if "." in curr_title:
        curr_title=curr_title.split(".")[0]
#        print curr_title

    if prev_title==curr_title:
#        print curr_line,
        continue
    else:
        count+=1
        print prev_line,


