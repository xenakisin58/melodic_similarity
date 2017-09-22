def median(lst):
    sortedLst = sorted(lst)
    lstLen = len(lst)
    index = (lstLen - 1) // 2

    if (lstLen % 2):
        return sortedLst[index]
    else:
        return (sortedLst[index] + sortedLst[index + 1])/2.0

from collections import Counter

#f = open("../../output_covers/la_modOctave.dat","r")
f = open("../../output_unique/ga_parsons.dat","r")

avg = 0.0
count = 0
list = []
for line in f.readlines():
    temp = line.split(";")
#    temp = line.split("|")
    for entry in temp:
        if entry != "\n" and entry != '':
#        if "No" not in entry and entry != "\n" and entry != '':
            temp_num = (float(entry.split(",")[1])/float(entry.split(",")[0]))
#            temp_num = int(entry.split("=")[1]) #ST - len
#            temp_num = max(int(entry.split(",")[0]),int(entry.split(",")[1])) #LA-len
            avg += temp_num
            list.append("%.4f" % temp_num)
            count +=1

print count,","
print float(avg/count),",",
print median(list),",",

data = Counter(list)
print data.most_common(1)[0][0],",",data.most_common(1)[0][1]
