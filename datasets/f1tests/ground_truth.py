songList = [] #for counting #unique covers
count = 0
f = open("../lakh_corr_dedupeEx_midi.dat","r")
content = f.readlines()
for i in range(0,len(content)):
    output_line = ""
    artist1 = content[i].split(";")[0]
    title1 = content[i].split(";")[1]
    if "." in title1[-2:]:
        title1 = title1[0:-2]
    for j in range(i+1,len(content)):
        artist2 = content[j].split(";")[0]
        title2 = content[j].split(";")[1]
        if "." in title2[-2:]:
            title2 = title2[0:-2]
        if title1 == title2 and title1 != "Sara" and title1 != "Don't Bring Me Down" and title1 != "First Time":
            output_line += "y,"
#check number of unique songs with covers
#            if [artist1,title1] not in songList:
#                songList.append([artist1,title1])
#                continue
##
#            if[artist1,title1] in songList:
#                count += 1
#            else:
#                count +=2

            if artist1!=artist2:
                 print "+++++",
            print  artist1,",",title1,"==",artist2,",",title2
            break
        else:
            output_line += "n,"
#    print output_line
print count
