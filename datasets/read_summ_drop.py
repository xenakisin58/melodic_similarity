#TTESTS COVERS
#f = open("../ttest/output_summer/st_modOctave.dat","r")

#f = open("../ttest/output_summer/la_parsons.dat","r")
#f = open("../ttest/output_summer/la_interval.dat","r")
#f = open("../ttest/output_summer/la_noteValMod.dat","r")
#f = open("../ttest/output_summer/la_rhythm.dat","r")
#f = open("../ttest/output_summer/la_modOctave.dat","r")

#TTESTS CONTROL
f = open("../ttest/output_control/la_parsons.dat","r")
#f = open("../ttest/output_control/la_interval.dat","r")
#f = open("../ttest/output_control/la_noteValMod.dat","r")
#f = open("../ttest/output_control/la_rhythm.dat","r")
#f = open("../ttest/output_control/la_modOctave.dat","r")

#DROP NOTES
#f = open("../output_summer_drop/st_parsons_ctl_drop5.dat","r")
#f = open("../output_summer_drop/la_parsons_ctl_drop5.dat","r")

line_no = 0
len_threshold = 200
for line in f.readlines():
#    line = line.split("|")
##    line = line.replace("|","=").split("=")
#    for i in range(0,len(line)):
#        if "No" in line[i]:
#            print "0",",",
#        else:
#            if line[i]!= '' and line[i] != "\n":
#                temp = line[i].split("=")[1]
#                print temp,",",
#    line_no +=1
##    print "\n",
##    for j in range(0,line_no):
##        print ",",

#GA and LA code
    line = line.split(";")
    for entry in line:
        if entry != "\n" and entry != '':
                max_len = max(int(entry.split(",")[0]),int(entry.split(",")[1]))	#
#                ga_len = entry.split(",")[0]
                if max_len == 0:
#                if ga_len == "0":
                    print "0.0"
                elif max_len < len_threshold:
                    print "0.0"
                else:
                    err = float(1-float(entry.split(",")[2])/float(max_len))		#
#                    err = float(1 - float(entry.split(",")[1])/float(entry.split(",")[0]))
                    print err,"\n",

    line_no +=1
#    print "\n",
#    for j in range(0,line_no):
#        print ",",
