from difflib import SequenceMatcher
def similar(a, b):
    return SequenceMatcher(None, a, b).ratio()

with open('lakh_corr_dedupeEx_midi.dat','r') as input:
    prev_title = curr_title = prev_line = curr_line = ""
    cover_count = 0
    ppmp_flag = 0 #false

    for index,line in enumerate(input):
        prev_line = curr_line
        curr_line = line
        prev_title = curr_title
        curr_title = line.split(";")[1]
        if curr_title[-2]==".":
            curr_title=curr_title[:-2]

        if prev_title==curr_title:
            sim = similar(prev_line,curr_line)
            if sim > 0.9: #remove duplicate renditions
                continue
            else:
#                print prev_line,
##                print prev_title
                with open('covers/lakh_cover_midi{}.dat'.format(cover_count),'a') as output:
                    output.write(prev_line)
                ppmp_flag = 1 #set true for next pass

        else:
            if ppmp_flag !=0: #if prev_prev matches prev titles
#                print prev_line,
##                print prev_title
                with open('covers/lakh_cover_midi{}.dat'.format(cover_count),'a') as output:
                    output.write(prev_line)
                cover_count = cover_count + 1
                ppmp_flag = 0 #reset to false
