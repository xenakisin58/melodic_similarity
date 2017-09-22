f = open("../lakh_corr_dedupeEx_midi.dat","r")
prev_artist = artist = prev_title = title = ""
cov_flag = False
content = f.readlines()
for i in range(0,len(content)):
    out_artist = content[i].split(";")[0]
    out_title = content[i].split(";")[1]
    for j in range(i+1,len(content)):
        artist = content[j].split(";")[0]
        title = content[j].split(";")[1]
        if out_title == title:
            cov_flag = True
            continue
        elif cov_flag == True:
            cov_flag = False
            print artist,",",title,"==",prev_artist,",",prev_title
