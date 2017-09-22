//#ifndef _READFILE_FUNCTIONS_
//#define _READFILE_FUNCTIONS_

//typedef struct note note;
//typedef struct melody melody;

typedef struct note{
    int note_val;
    int dur;
    struct note * next;
}note;

typedef struct melody{
    int length;
    note * head;
    int tpb;
    int key;
    int meter;
    struct melody * next;
}melody;

/* Prints entire dataset to STDOUT starting from
   melody * start (aka head of melody dataset)*/
void print_melody_data(melody * start);

/* Reads dataset from specified filename and returns pointer
   to head melody of dataset. */
melody* read_melody_dataset(FILE * fp, char * filename);

void freeData(melody* head);
//#endif

