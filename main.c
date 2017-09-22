#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <readData.h>
#include <suffixTree.h>
#include <musicFunctions.h>
#include <alignment.h>

#define _GNU_SOURCE
extern Node *root;

void writeParsonsDrop(melody* iter_left, melody* iter_right,int drop_val);

//PROTOTYPES- PAIRWISE SEQUENCE ALIGNMENT
void testRhythm_nw(melody* iter_left, melody* iter_right);
void testRhythm_sw(melody* iter_left, melody* iter_right);
void testModOctave_nw(melody* iter_left, melody* iter_right);
void testModOctave_sw(melody* iter_left, melody* iter_right);

//PROTOTYPES - SUFFIX TREE
void testExplicit(melody* iter_left,melody* iter_right);
void testModOctave(melody* iter_left,melody* iter_right);
void testRhythm(melody* iter_left,melody* iter_right);
void testNoteValMod(melody* iter_left,melody* iter_right);
void testInterval(melody* iter_left,melody* iter_right);
void testIntervalMod(melody* iter_left,melody* iter_right);
void testParsons(melody* iter_left, melody* iter_right);
void writeExplicit(melody* iter_left,melody* iter_right,int* shift1, int* shift2, int* tshift1,int* tshift2);
void writeRhythm(melody* iter_left,melody* iter_right, int* tshift1, int* tshift2);
void writeModOctave(melody* iter_left,melody* iter_right,int* tshift1,int* tshift2);
void writeNoteValMod(melody* iter_left,melody* iter_right);
void writeInterval(melody* iter_left,melody* iter_right);
void writeIntervalMod(melody* iter_left,melody* iter_right);
void writeParsons(melody* iter_left,melody* iter_right);

/* MAIN */
int main(void){
    FILE * fp=NULL;
//UNIQUE MELODIES
    char * filename = "datasets/lakh_corr_unique_midi.dat";
//UNIQUE MELODES AND COVERS
//    char * filename = "datasets/lakh_corr_deduleEx_midi.dat";

//TTESTS
//     char * filename = "datasets/summer_cover_midi.dat";
//     char * filename = "datasets/summer_cover_control.dat";
//COVER DETECTION
//     char * filename = "datasets/jazz_cover_needle-haystack/summer_test50.dat";

    melody* dataset_start = read_melody_dataset(fp, filename);

    //Initialize
    melody * iter_left = dataset_start;
    melody * iter_right = dataset_start->next;

//    int drop_val = 5;
    while(iter_left->next != NULL){
        while(iter_right != NULL){
            //Suffix Tree tests
//            testExplicit(iter_left,iter_right);
//            testModOctave(iter_left,iter_right);
//            testRhythm(iter_left,iter_right);
//            testNoteValMod(iter_left,iter_right);
//            testInterval(iter_left,iter_right);
//            testIntervalMod(iter_left,iter_right);
            testParsons(iter_left,iter_right);


            //Drop Embellishing Tones Successively
//            writeParsonsDrop(iter_left,iter_right,drop_val);
//            nw_heap(size1,size-(size1+2));
//            sw_heap(size1,size-(size1+2));
//            buildSuffixTree(size);
//            getLongestCommonSubstring();
            //getLongestRepeatedSubstring();
//            freeSuffixTreeByPostOrder(root); //Free the dynamically allocated memory
//            reinitialize();


            //GLOBAL ALIGNMENT
//            if(iter_left->length >= iter_right->length/2 && iter_left->length <= (iter_right->length * 2)){
//                testModOctave_nw(iter_left, iter_right);
//                testRhythm_nw(iter_left, iter_right);
//                writeNoteValMod(iter_left, iter_right);
//                writeInterval(iter_left, iter_right);
//                writeParsons(iter_left, iter_right);
//                nw_heap(size1,size-(size1+2));
//            }
//            else{printf(";");}
            //LOCAL ALIGNMENT
//            testModOctave_sw(iter_left, iter_right);
//            testRhythm_sw(iter_left, iter_right);
//            writeNoteValMod(iter_left, iter_right);
//            writeInterval(iter_left, iter_right);
//            writeParsons(iter_left,iter_right);
//            sw_heap(size1,size-(size1+2));

             //advance right iterator
            iter_right = iter_right->next;
        }
        iter_left = iter_left->next;
        iter_right = iter_left->next;
        printf("\n");
    }
    freeData(dataset_start);
    return 0;
}

void testModOctave_nw(melody* iter_left, melody* iter_right){
    int i;
    int tshift1=1, tshift2=1;
    best_score = 2.0;
    best_length = 0;
    best_edits = 0;
    for(i=0; i<3; i++){
        if(i==1){tshift1=1; tshift2=2;}
        if(i==2){tshift1=2; tshift2=1;}
        writeModOctave(iter_left, iter_right,&tshift1,&tshift2);
        nw_heap(iter_left->length, iter_right->length);
    }
    printf("%d,%d;",best_length,best_edits);
    fflush(stdout);
}

void testModOctave_sw(melody* iter_left, melody* iter_right){
    int i;
    int tshift1=1, tshift2=1;
    best_score = 1.0;
    best_length = 0;
    best_edits = 0;
    for(i=0; i<3; i++){
        if(i==1){tshift1=1; tshift2=2;}
        if(i==2){tshift1=2; tshift2=1;}
        writeModOctave(iter_left, iter_right,&tshift1,&tshift2);
        sw_heap(iter_left->length, iter_right->length);
    }
    printf("%d,%d,%d;",best_length_a,best_length_b,best_edits);
    fflush(stdout);
}

void testRhythm_nw(melody* iter_left, melody* iter_right){
    int i;
    int tshift1=1, tshift2=1;
    best_score = 2.0;
    best_length = 0;
    best_edits = 0;
    for(i=0; i<3; i++){
        if(i==1){tshift1=1; tshift2=2;}
        if(i==2){tshift1=2; tshift2=1;}
        writeRhythm(iter_left, iter_right,&tshift1,&tshift2);
        nw_heap(iter_left->length, iter_right->length);
    }
    printf("%d,%d;",best_length,best_edits);
    fflush(stdout);
}

void testRhythm_sw(melody* iter_left, melody* iter_right){
    int i;
    int tshift1=1, tshift2=1;
    best_score = 1.0;
    best_length = 0;
    best_edits = 0;
    for(i=0; i<3; i++){
        if(i==1){tshift1=1; tshift2=2;}
        if(i==2){tshift1=2; tshift2=1;}
        writeRhythm(iter_left, iter_right,&tshift1,&tshift2);
        sw_heap(iter_left->length, iter_right->length);
    }
    printf("%d,%d,%d;",best_length_a,best_length_b,best_edits);
    fflush(stdout);
}

//compares the explicit form of melody representation
void testExplicit(melody* iter_left, melody* iter_right){
    int i,j;
    int shift1=0;
    int shift2=0;
    int tshift1=1;
    int tshift2=1;
    for(i=0;i<3;i++){ //shift octaves
        if(i==1){shift1=12; shift2=0;}
        if(i==2){shift1=0; shift2=12;}
        for(j=0;j<3;j++){ //shift tempos (half vs. double)
            if(j==1){tshift1=1; tshift2=2;}
            if(j==2){tshift1=2; tshift2=1;}
            writeExplicit(iter_left, iter_right,&shift1,&shift2,&tshift1,&tshift2);
            //suffixTree Calls:
            buildSuffixTree(size);
            getLongestCommonSubstring();
            //Free the dynamically allocated memory
            freeSuffixTreeByPostOrder(root);
            reinitialize();
        }
    }
}

void testModOctave(melody* iter_left, melody* iter_right){
    int tshift1=1;
    int tshift2=1;
    best_length = 0;
//    memset(best_seq,0,sizeof(best_seq));
    for(int i=0;i<3;i++){
        if(i==1){tshift1=1; tshift2=2;}
        if(i==2){tshift1=2; tshift2=1;}
        //write melodies and test
        writeModOctave(iter_left, iter_right,&tshift1,&tshift2);
        //suffixTree Calls:
        buildSuffixTree(size);
        getLongestCommonSubstring_bestOfThree();
//        getLongestRepeatedSubstring_bestOfThree();
        //Free the dynamically allocated memory
        freeSuffixTreeByPostOrder(root);
        reinitialize();
    }
    //print best result of 3 comparisos (tempo shifts)
    if(best_length>0){
        for(int i=0; i<best_length; i++){
            printf("%d,",best_seq[i]-2);
        }
        printf(";l=%d|",best_length);
    }
    else{printf("No common substring|");}
    fflush(stdout);
}

void testRhythm(melody* iter_left,melody* iter_right){
    int tshift1=1;
    int tshift2=1;
    best_length = 0;
//    memset(best_seq,0,sizeof(best_seq));
    for(int i=0;i<3;i++){
        if(i==1){tshift1=1; tshift2=2;}
        if(i==2){tshift1=2; tshift2=1;}
        //write rhythms and test
        writeRhythm(iter_left, iter_right,&tshift1,&tshift2);
        //suffixTree Calls:
        buildSuffixTree(size);
        getLongestCommonSubstring_bestOfThree();
//    getLongestRepeatedSubstring_bestOfThree();
        //Free the dynamically allocated memory
        freeSuffixTreeByPostOrder(root);
        reinitialize();
    }
    //print best result of 3 comparisos (tempo shifts)
    if(best_length>0){
        for(int i=0; i<best_length; i++){
            printf("%d,",best_seq[i]-2);
        }
        printf(";l=%d|",best_length);
    }
    else{printf("No common substring|");}
    fflush(stdout);
}

void testNoteValMod(melody* iter_left,melody* iter_right){
    writeNoteValMod(iter_left, iter_right);
    //suffixTree Calls:
    buildSuffixTree(size);
    getLongestCommonSubstring();
//    getLongestRepeatedSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
    reinitialize();
}
void testInterval(melody* iter_left,melody* iter_right){
    writeInterval(iter_left, iter_right);
    //suffixTree Calls:
    buildSuffixTree(size);
    getLongestCommonSubstring();
//    getLongestRepeatedSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
    reinitialize();
}

void testIntervalMod(melody* iter_left,melody* iter_right){
    writeIntervalMod(iter_left, iter_right);
    //suffixTree Calls:
    buildSuffixTree(size);
    getLongestCommonSubstring();
//    getLongestRepeatedSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
    reinitialize();
}
void testParsons(melody* iter_left, melody* iter_right){
    writeParsons(iter_left, iter_right);
    //suffixTree Calls:
    buildSuffixTree(size);
    getLongestCommonSubstring();
//    getLongestRepeatedSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
    reinitialize();
}

void writeExplicit(melody* iter_left, melody* iter_right,int* shift1, int* shift2,int* tshift1,int* tshift2){
    int i;
    size1 = iter_left->length;
    size = size1 + iter_right->length + 2;
    note* np = iter_left->head;
    for(i=0;i<size1;i++){
        text[i] = 2 + encode(np->note_val + *shift1,quantize(np->dur,(iter_left->tpb * (*tshift1)),iter_left->meter));
        np=np->next;
    }
//    text[i] = MAX_CHAR-2; //assign the seperator 'character'
    text[i] = 0; //assign the seperator 'character'
    i++;
    np = iter_right->head;
    for(;i<size;i++){
        text[i] = 2 + encode(np->note_val+transpose(iter_left->key,iter_right->key) + *shift2,quantize(np->dur,(iter_right->tpb * (*tshift2)),iter_right->meter));
        np=np->next;
    }
//    text[i] = MAX_CHAR-1; //assign the termination 'character'
    text[i] = 1; //assign the termination 'character'
}

void writeModOctave(melody* iter_left, melody* iter_right,int* tshift1,int* tshift2){
    int i;
    size1 = iter_left->length;
    size = size1 + iter_right->length + 2;
    note* np = iter_left->head;
    for(i=0;i<size1;i++){
        text[i] = 2 + encode(np->note_val%12,quantize(np->dur,(iter_left->tpb * (*tshift1)),iter_left->meter));
        np=np->next;
//        printf("%d,",text[i]);
    }
//    text[i] = MAX_CHAR-2; //assign the seperator 'character'
    text[i] = 0; //assign the seperator 'character'
//    printf("%d,",text[i]);
    i++;
    np = iter_right->head;
    for(;i<size;i++){
        text[i] = 2 + encode((np->note_val+transpose(iter_left->key,iter_right->key))%12,quantize(np->dur,(iter_right->tpb * (*tshift2)),iter_right->meter));
        np=np->next;
//        printf("%d,",text[i]);
    }
//    text[i] = MAX_CHAR-1; //assign the termination 'character'
    text[i] = 1; //assign the termination 'character'
//    printf("%d\n",text[i]);
}

void writeRhythm(melody* iter_left,melody* iter_right, int* tshift1, int* tshift2){
    int i;
    size1 = iter_left->length;
    size = size1 + iter_right->length + 2;
    note* np = iter_left->head;
    for(i=0;i<size1;i++){
        text[i] = 2 + quantize(np->dur,(iter_left->tpb * (*tshift1)), iter_left->meter);
        np=np->next;
//        printf("%d,",text[i]-2);
    }
//    text[i] = MAX_CHAR-2; //assign the seperator 'character'
    text[i] = 0; //assign the seperator 'character'
//    printf("%d,",text[i]);
//    printf("#,");
    i++;
    np = iter_right->head;
    for(;i<size;i++){
        text[i] = 2 + quantize(np->dur,(iter_right->tpb * (*tshift2)), iter_right->meter);
        np=np->next;
//        printf("%d,",text[i]-2);
    }
//    text[i] = MAX_CHAR-1; //assign the termination 'character'
    text[i] = 1; //assign the termination 'character'
//    printf("%d\n",text[i]);
//    printf("$\n");
}

void writeNoteValMod(melody* iter_left,melody* iter_right){
    int i;
    size1 = iter_left->length;
    size = size1 + iter_right->length + 2;
    note* np = iter_left->head;
    for(i=0;i<size1;i++){
        text[i] = 2 + (np->note_val % 12);
        np=np->next;
//        printf("%d ",text[i]-2);
//        printf("%c",(char)(text[i] + 97-2));
    }
//    text[i] = MAX_CHAR-2; //assign the seperator 'character'
    text[i] = 0; //assign the seperator 'character'
//    printf("%c",(char)text[i]);
//    printf("# ");
    i++;
    np = iter_right->head;
    for(;i<size;i++){
        text[i] = 2 + ((np->note_val+transpose(iter_left->key,iter_right->key))%12);
        if(text[i]<2){text[i]+=12;}
        np=np->next;
//        printf("%d ",text[i]-2);
//        printf("%c",(char)(text[i]-2+97));
    }
//    text[i] = MAX_CHAR-1; //assign the termination 'character'
    text[i] = 1; //assign the termination 'character'
//    printf("%d\n",text[i]);
//    printf("$\n");
}

void writeInterval(melody* iter_left,melody* iter_right){
    int i;
    note* np = iter_left->head;
    size1 = iter_left->length-1;
    size = size1 + iter_right->length;
    for(i=0;i<size1;i++){
        text[i] = 2 + interval(np->note_val,np->next->note_val)+127;
        np=np->next;
//        printf("%d ",text[i]-129);
    }
//    text[i]=MAX_CHAR-2;
    text[i]=0;
//    printf("%d,",text[i]);
    i++;
    np = iter_right->head;
//    printf("  %d  ",text[i]);
    for(;i<size-1;i++){
        text[i] = 2 + interval(np->note_val,np->next->note_val)+127;
//        printf("%d ",text[i]-129);
//    printf("%d",text[i]-129);
        np=np->next;
//if(text[i]<2){printf("FUCK");}
    }
//    text[i]=MAX_CHAR-1;
    text[i]=1;
//    printf("% d\n",text[i]);
}

void writeIntervalMod(melody* iter_left,melody* iter_right){
    int i;
    size1 = iter_left->length-1;
    size = size1 + iter_right->length;
    note* np = iter_left->head;
    for(i=0;i<size1;i++){
        text[i] = 2 + intervalMod(np->note_val,np->next->note_val)+12;
        np=np->next;
    }
//    text[i]=MAX_CHAR-2;
    text[i]=0;
    i++;
    np = iter_right->head;
    for(;i<size-1;i++){
        text[i] = 2 + intervalMod(np->note_val,np->next->note_val)+12;
        np=np->next;
    }
//    text[i]=MAX_CHAR-1;
    text[i]=1;
}

void writeParsons(melody* iter_left,melody* iter_right){
    int i;
    size1 = iter_left->length-1;
    size = size1 + iter_right->length;
    note* np = iter_left->head;
    for(i=0;i<size1;i++){
        text[i] = 2 + parsons(np->note_val,np->next->note_val);
        np=np->next;
//printf("%d",text[i]-2);
    }
//    text[i]=MAX_CHAR-2;
    text[i] = 0;
    i++;
//printf("#");
    np = iter_right->head;
    for(;i<size-1;i++){
        text[i] = 2 + parsons(np->note_val,np->next->note_val);
        np=np->next;
//printf("%d",text[i]-2);
    }
//    text[i]=MAX_CHAR-1;
    text[i]=1;
//printf("$\n");
}

void writeParsonsDrop(melody* iter_left, melody* iter_right,int drop_val){
    int i,temp;
    size1 = iter_left->length-1;
    size = size1 + iter_right->length;
    note* np = iter_left->head;
    for(i=0;i<size1;i++){
        temp = quantize(np->dur,iter_left->tpb,iter_left->meter);
        if(temp >= (int) pow(2,drop_val)){
            //...
//printf("temp=%d >= pow(2,%d)=%d\n",temp,drop_val,(int) pow(2,drop_val));
            text[i] = 2 + parsons(np->note_val,np->next->note_val);
//printf("%d,",text[i]);
        }
        else{
//printf("temp=%d < pow(2,%d)=%d ... not adding to string\n",temp,drop_val,(int) pow(2,drop_val));
            i--;
            size1-=1;
            size-=1;
        }
        np=np->next;
    }
//    text[i]=MAX_CHAR-2;
    text[i] = 0;
    i++;
//printf("#,");
    np = iter_right->head;
    for(;i<size-1;i++){
//printf("temp=%d\n");
        temp = quantize(np->dur,iter_right->tpb,iter_right->meter);
        if(temp >= (int) pow(2,drop_val)){
//printf("temp=%d >= pow(2,%d)=%d\n",temp,drop_val,(int) pow(2,drop_val));
            text[i] = 2 + parsons(np->note_val,np->next->note_val);
//printf("%d,",text[i]);
        }
        else{
//printf("temp=%d < pow(2,%d)=%d ... not adding to string\n",temp,drop_val,(int) pow(2,drop_val));
            i--;
            size-=1;
        }
        np=np->next;
    }
//    text[i]=MAX_CHAR-1;
    text[i]=1;
//printf("$\n");
}
