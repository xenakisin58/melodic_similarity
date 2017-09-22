#IMPORTS
from sklearn.metrics import f1_score, precision_score, recall_score
import numpy as np

#classifier for Inexact Matching
err_threshold = 0.4
#classifier for Exact Matching
length_threshold = 2 #should this be some fraction of the total length?

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

for i in range(0,100):
    pred = np.random.randint(2, size=len(gt))
#print(len(pred))

    #Analysis Routines
    precision = precision_score(gt, pred, average='binary')
    recall = recall_score(gt, pred, average = 'binary')
    f1 = f1_score(gt, pred,average='binary')
    print(precision,",",recall,",",f1)
