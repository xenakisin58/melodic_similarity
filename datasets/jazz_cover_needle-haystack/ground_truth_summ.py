f = open("summer_test1.dat","r")
content = f.readlines()
output=""
for i in range(0,len(content)):
    for j in range(i+1,len(content)):
        title = content[j].split(";")[1].upper()
        if "SUMMERTIME" in title:
            output+="y,"
        else:
            output+="n,"
    output+="\n"
print output
