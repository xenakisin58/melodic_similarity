#IMPORTS
from sklearn.metrics import f1_score, precision_score, recall_score

#classifier for Inexact Matching
err_threshold = 0.4
#classifier for Exact Matching
length_threshold = 2 #should this be some fraction of the total length?

#Read Ground Truth data
#f = open("ground_truth.dat","r")
f = open("../summer_cover_detection/gt1.dat","r")
gt = []
for line in f.readlines():
    tmp = line.strip("\n").split(",")
    while '' in tmp:
        tmp.remove('')
    for entry in tmp:
        if entry == 'y':
            gt.append(1)
        elif entry == 'n':
            gt.append(0)
        else:
            continue
f.close()

for i in range(1,21,2):
#    print length_threshold,","
    pred = []
#    f = open("../../output_covers/st_modOctave.dat","r")
    f = open("../../output_summer_test/st_rhythm1.dat","r")
    ## perform test with various thresholds to get prediction data
    for line in f.readlines():
        line = line.strip("\n").split("|")
        for entry in line:
            if "No" in entry:
                pred.append(0)
                continue
            elif entry == "\n" or entry == '':
                continue
            else:
                if int(entry.split("=")[1]) >= length_threshold:
                    pred.append(1)
                else:
                    pred.append(0)

    f.close()
    length_threshold +=2

    #Analysis Routines
    precision = precision_score(gt, pred, average='binary')
    recall = recall_score(gt, pred, average = 'binary')
    f1 = f1_score(gt, pred,average='binary')
    print precision,",",recall,",",f1
