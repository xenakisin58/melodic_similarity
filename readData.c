#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"

// Prints entire dataset to STDOUT starting from
//   melody * start (aka head of melody dataset)
void print_melody_data(melody * start){
    note * curr_note;
    while(start!=NULL){
        curr_note = start->head;
        while(curr_note!=NULL){
            printf("%d,%d;",curr_note->note_val,curr_note->dur);
            curr_note=curr_note->next;
        }printf("\n");
        start = start->next;
    }
}

/* Reads dataset from specified filename and returns pointer
   to head melody of dataset. */
melody* read_melody_dataset(FILE * fp, char * filename){
    char * line = NULL;
    //char * meta = NULL;
    char * temp = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("File Access Error.\n");
        exit(EXIT_FAILURE);
    }
    melody * head_mel;
    melody * tail_mel;
    int firstPass=1;

    while ((read = getline(&line, &len, fp)) != -1) {
        char* line2 = line;
        melody * m = (melody*)calloc(1,sizeof(melody));
        m->length = 0;
        strtok(line2,";"); //artist - not using
        strtok(NULL,";"); //track title - not using
        m->tpb = atoi(strtok(NULL,";")); //tpb
        m->key = atoi(strtok(NULL,";")); //keySig 0-23
        m->meter = atoi(strtok(NULL,"/")); //meter
        strtok(NULL, "|"); //time sig and tempo - not using
        note * n1 = (note*)calloc(1,sizeof(note));
//        note* n1 = (note*)malloc(sizeof(note));
        note *curr;
        curr = n1;
        n1->note_val = atoi(strtok(NULL,","));
        n1->dur = atoi(strtok(NULL,";"));
        m->head = n1;
        while(1){ //get notes from track
            note *n = (note*) calloc(1,sizeof(note));
            temp = strtok(NULL,",");
            if(temp==NULL){n->next = NULL; free(n); break;}
            n->note_val = atoi(temp);
            temp = strtok(NULL,";");
            if(temp==NULL){n->next = NULL; free(n); break;}
            n->dur = atoi(temp);
            curr->next = n;
            curr = curr->next;
            m->length++;
        }
        if(firstPass){
            tail_mel = m;
            head_mel = m;
            firstPass=0;
        }
        else{
            tail_mel->next = m;
            tail_mel = tail_mel->next;
        }
    }
    if (line)
        free(line);
    fclose(fp);
    return head_mel;
}

void freeData(melody* head){
    melody* curr_mel = head;
    while(head!=NULL){
        curr_mel = head;
        head = head->next;
        note* curr_note;
        while(curr_mel->head!=NULL){
            curr_note = curr_mel->head;
            curr_mel->head = curr_mel->head->next;
            free(curr_note);
        }
//        free(curr_mel->head);
        free(curr_mel);
    }
    free(head);
}
