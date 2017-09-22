#IMPORTS
from sklearn.metrics import f1_score, precision_score, recall_score

#classifier for Inexact Matching
err_threshold = 1.0
#classifier for Exact Matching
length_threshold = 3 #should this be some fraction of the total length?

#Read Ground Truth data
f = open("ground_truth.dat","r")
#f = open("../summer_cover_detection/gt1.dat","r")
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

for i in range(100,0,-5):
#    print length_threshold,","
    pred = []
    f = open("../../output_covers/la_modOctave.dat","r")
#    f = open("../../output_summer_test/ga_rhythm1.dat","r")
    ## perform test with various thresholds to get prediction data
    for line in f.readlines():
        line = line.strip("\n").split(";")
        for entry in line[:-1]:
            if entry == "\n":
                continue
#            if entry == '':
#                pred.append(0)
            else:
                #LA
                longest = max(int(entry.split(",")[0]),int(entry.split(",")[1]))
###                print entry.split(",")[2]," / ",str(longest)
                if longest < length_threshold: #should be <= 0 even if no threshold
                    pred.append(0)
                elif float(entry.split(",")[2])/float(longest) <= err_threshold:
                    pred.append(1)
                #GA
#                if float(entry.split(",")[1])/float(entry.split(",")[0]) <= err_threshold:
#                    pred.append(1)
                else:
                    pred.append(0)

    f.close()
    err_threshold -=0.05

    #Analysis Routines
    precision = precision_score(gt, pred, average='binary')
    recall = recall_score(gt, pred, average = 'binary')
    f1 = f1_score(gt, pred,average='binary')
    print precision,",",recall,",",f1

#precision, recall, thresholds = precision_recall_curve(y_true, y_scores)
