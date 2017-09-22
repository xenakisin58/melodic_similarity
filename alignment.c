/* A program to implement the Smith-Waterman Local Alignment
 * Algorithm  */

#include <stdio.h>
#include <stdlib.h>

//For LA Algorithm
int match = 1;//10;
int mismatch = -1;//-5;
int gap = 1;
//int gappenalty = 1;//10;
//int gapextension = 1;//8;

extern int text[50000];

int best_length;
int best_length_a;
int best_length_b;
int best_edits;
double best_score;

enum flag{
    up,
    left,
    diagonal
};

int max3(int a, int b, int c){
    int temp = (a>b)?a:b;
    return((temp>c)?temp:c);
}

//for SW
int max4(int a, int b, int c, int d){
    int temp1, temp2;
    temp1 = (a>b)?a:b;
    temp2 = (c>d)?c:d;
    return (temp1>temp2)?temp1:temp2;
}

//accessing table entries on heap to read
int access(int i, int j, int n, int * table){
    return *(table + (n*i) + j);
}

//accessing table entries on heap to write
int * access_w(int i, int j, int n, int * table){
    return (table + (n*i) + j);
}

/* Prints the dynamic programming alignment table
 * for Smith-Waterman and Needleman-Wunsch */
void print_table(int m, int n, int * table){
    int i,j;
    for(i=0; i<m; i++){
        for(j=0;j<n;j++){
            printf("%d ",access(i,j,n,table));
        }printf("\n");
    }
}

void backtrace_sw(int m, int n, int i, int j, int * la_table){
//    printf("%d @ [%d][%d]; ",la_table[posA][posB],posA,posB);
    int temp_max=1,tm_r=0,tm_c=0;
    int length_a=1,length_b=1,edits=0;
    enum flag sw_flag;

    while(temp_max > 0){
        temp_max=0;
        if(access(i-1,j,n,la_table)!=0 && access(i,j-1,n,la_table)!=0){
            //check left
            if(access(i,j-1,n,la_table)>temp_max){
                temp_max = access(i,j-1,n,la_table);
                tm_r = i; tm_c = j-1;
                sw_flag = left;
            }
            //check up
            if(access(i-1,j,n,la_table)>temp_max){
                temp_max = access(i-1,j,n,la_table);
                tm_r = i-1; tm_c = j;
                sw_flag = up;
            }
        }
        //check diagnoal
        if(access(i-1,j-1,n,la_table)>=temp_max && i>1 && j>1){
            temp_max = access(i-1,j-1,n,la_table);
            tm_r = i-1; tm_c = j-1;
            sw_flag = diagonal;
        }
        if(temp_max==0 &&(i==1 || j==1)){break;}
        //update length & edits
        if(sw_flag == up){
            length_a += i-tm_r;
            length_b++;
            edits += i-1-tm_r;
        }
        else if(sw_flag == left){
            length_a++;
            length_b += j-tm_c;
            edits += j-1-tm_c;
        }
        else{
            length_a++;
            length_b++;
            if(text[i-1]!=text[m+j-1]){
                edits++;
            }
        }
        //update positions
        i = tm_r; j = tm_c;
    }
    //last character check edit score
    if(text[i-1]!=text[m+j-1] && (i>1 || j>1)){edits++;}
    //output data
    printf("%d,%d,%d;",length_a,length_b,edits);
    fflush(stdout);
}

void sw(int m, int n){
    m+=1; n+=1;
    int * la_table = calloc(m*n,sizeof(int));
    int hi_r=0, hi_c=0, hi_val=0;
    //populate DP table
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            //0th row and col should all be 0's
            if(i==0||j==0){*access_w(i,j,n,la_table)=0;}
            else{
                //match
                if(text[i-1]==text[m+j]){
                    *access_w(i,j,n,la_table) = *(la_table + (n*(i-1)) + (j-1)) + match;
                }
                //mismatch
                else{
                *access_w(i,j,n,la_table) = max3(access(i-1,j,n,la_table)-gap,
                            access(i,j-1,n,la_table)-gap,access(i-1,j-1,n,la_table)+mismatch);
                }
                if(access(i,j,n,la_table)<0){*access_w(i,j,n,la_table)=0;}
                //keep track of best score
                if(access(i,j,n,la_table)>hi_val){hi_val=access(i,j,n,la_table);hi_r=i;hi_c=j;}
            }
        }
    }
//    print_table(m,n,la_table);
//    printf("%d,",hi_val);//printf("max=%d,",hi_val);
    //printf("hi_val=%d @ [%d][%d]\n",hi_val,hi_r,hi_c);
    backtrace_sw(m,n,hi_r,hi_c,la_table);
}


/* **************************************************** */


/* Backtrace algorithm for Smith-Waterman
   implemented on the stack */
void backtrace_sw_stack(int m, int n, int i, int j, int la_table[m][n]){
    //printf("%d @ [%d][%d]\n",la_table[i][j],i,j);
    int temp_max=1,tm_r=0,tm_c=0;
    int length_a=0,length_b=0,edits=0;
    enum flag sw_flag;

    while(i > 0 || j > 0){
        temp_max=0;
        //check left
        if(j > 0 && la_table[i][j-1]>temp_max){
            temp_max = la_table[i][j-1];
            tm_r = i; tm_c = j-1;
            sw_flag = left;
        }
        //check up
        if(i > 0 && la_table[i-1][j]>temp_max){
            temp_max = la_table[i-1][j];
            tm_r = i-1; tm_c = j;
            sw_flag = up;
        }
        //check diagnoal
        if(i > 0 && j > 0 && la_table[i-1][j-1] >= temp_max){
            temp_max = la_table[i-1][j-1];
            tm_r = i-1; tm_c = j-1;
            sw_flag = diagonal;
        }
        //update length & edits
        if(sw_flag == up){
            length_a++;
            edits += gap;
//printf("gap_up\n");
        }
        else if(sw_flag == left){
            length_b++;
            edits += gap;
//printf("gap_left\n");
        }
        else{
            length_a++;
            length_b++;
            if(text[i-1]!=text[m+j-1]){
//printf("%c @ %d != %c @%d\n",text[i-1],i-1, text[m+j-1],m+j-1);
                edits += (-mismatch);;
            }
        }
        //update positions
        i = tm_r; j = tm_c;
        if(temp_max <= 0){break;}
//        printf("%d @ [%d][%d]\n",temp_max,i,j);
//printf("%c!=%c\n",text[i-1], text[m+j-1]);
    }
    //output data
    //printf("%d @ [%d][%d]\n",temp_max,i,j);
    printf("%d,%d,%d;",length_a,length_b,edits);
    fflush(stdout);
}

/* A stack-based implementation of Smith-Waterman
   Local Alignment with an alphabet of type (int) */
void sw_stack(int m, int n){
    m+=1; n+=1;
//    int * la_table = calloc(m*n,sizeof(int));
    int la_table[m][n];
    int hi_val=0, hi_r=0, hi_c=0;
    //populate DP table
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            //0th row and col should all be 0's
            if(i==0||j==0){la_table[i][j]=0;}
            else{
                //match
                if(text[i-1]==text[m+j-1]){
//printf("%d==%d\n",text[i-1],text[m+j-1]);
                    la_table[i][j] = la_table[i-1][j-1] + match;
                }
                //mismatch
                else{
//printf("%d!=%d\n",text[i-1],text[m+j-1]);
                la_table[i][j] = max3(la_table[i-1][j] - gap,
                            la_table[i][j-1] - gap,la_table[i-1][j-1] + mismatch);
                }
                if(la_table[i][j] < 0){la_table[i][j]=0;}
                //keep track of best score
                if(la_table[i][j] > hi_val){
                    hi_val=la_table[i][j];
                    hi_r = i;
                    hi_c = j;
                }
            }
        }
    }
//    print_table(m,n,la_table);
//    printf("%d,",hi_val);//printf("max=%d,",hi_val);
    //printf("hi_val=%d @ [%d][%d]\n",hi_val,hi_r,hi_c);
    backtrace_sw_stack(m,n,hi_r,hi_c,la_table);
}

/* **************************************************** */


/* Backtrace algorithm for Smith-Waterman
   implemented on the heap */
void backtrace_sw_heap(int m, int n, int i, int j, int* la_table){
    //printf("%d @ [%d][%d]\n",la_table[i][j],i,j);
    int temp_max=1,tm_r=0,tm_c=0;
    int length_a=0,length_b=0,edits=0;
    enum flag sw_flag;

    while(i > 0 || j > 0){
        temp_max=0;
        //check left
        if(j > 0 && access(i,j-1,n,la_table) > temp_max){
            temp_max = access(i,j-1,n,la_table);
            tm_r = i; tm_c = j-1;
            sw_flag = left;
        }
        //check up
        if(i > 0 && access(i-1,j,n,la_table) > temp_max){
            temp_max = access(i-1,j,n,la_table);
            tm_r = i-1; tm_c = j;
            sw_flag = up;
        }
        //check diagnoal
        if(i > 0 && j > 0 && access(i-1,j-1,n,la_table) >= temp_max){
            temp_max = access(i-1,j-1,n,la_table);
            tm_r = i-1; tm_c = j-1;
            sw_flag = diagonal;
        }
        //update length & edits
        if(sw_flag == up){
            length_a++;
            edits += gap;
//printf("gap_up\n");
        }
        else if(sw_flag == left){
            length_b++;
            edits += gap;
//printf("gap_left\n");
        }
        else{
            length_a++;
            length_b++;
            if(text[i-1]!=text[m+j-1]){
//printf("%c @ %d != %c @%d\n",text[i-1],i-1, text[m+j-1],m+j-1);
                edits += (-mismatch);;
            }
        }
        //update positions
        i = tm_r; j = tm_c;
        if(temp_max <= 0){break;}
//        printf("%d @ [%d][%d]\n",temp_max,i,j);
//printf("%c!=%c\n",text[i-1], text[m+j-1]);
    }
    //output data
    //printf("%d @ [%d][%d]\n",temp_max,i,j);

    printf("%d,%d,%d;",length_a,length_b,edits);
    fflush(stdout);
/*
    int len_longer = (length_a > length_b)?length_a:length_b;
    if((float)edits/(float)len_longer < best_score && length_a > 0 && length_b > 0){
        best_length_a = length_a;
        best_length_b = length_b;
        best_edits = edits;
        best_score = (float)edits/(float)len_longer;
//printf("\nUPDATE: best_score = %lf\n",best_score);
    }
    // if # errors is 0, still need to improve the best length of match
    if((float)edits/(float)len_longer == best_score && (length_a > best_length_a || length_b > best_length_b)){
//printf ("len_longer was %d, now is %d or %d\n",len_longer, length_a, length_b);
        best_length_a = length_a;
        best_length_b = length_b;
        best_edits = edits;
        best_score = (float)edits/(float)len_longer;
    }
*/
}

/* A heap-based implementation of Smith-Waterman
   Local Alignment with an alphabet of type (int) */
void sw_heap(int m, int n){
    m+=1; n+=1;
    int * la_table = calloc(m*n,sizeof(int));
    int hi_val=0, hi_r=0, hi_c=0;
    //populate DP table
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            //0th row and col should all be 0's
            if(i==0||j==0){*access_w(i,j,n,la_table)=0;}
            else{
                //match
                if(text[i-1]==text[m+j-1]){
//printf("%d==%d\n",text[i-1],text[m+j-1]);
                    *access_w(i,j,n,la_table) = access(i-1,j-1,n,la_table) + match;
                }
                //mismatch
                else{
//printf("%d!=%d\n",text[i-1],text[m+j-1]);
                *access_w(i,j,n,la_table) = max3(access(i-1,j,n,la_table) - gap,
                            access(i,j-1,n,la_table) - gap, access(i-1,j-1,n,la_table) + mismatch);
                }
                if(access(i,j,n,la_table) < 0){*access_w(i,j,n,la_table)=0;}
                //keep track of best score
                if(access(i,j,n,la_table) > hi_val){
                    hi_val=access(i,j,n,la_table);
                    hi_r = i;
                    hi_c = j;
                }
            }
        }
    }
//    print_table(m,n,la_table);
//    printf("%d,",hi_val);//printf("max=%d,",hi_val);
    //printf("hi_val=%d @ [%d][%d]\n",hi_val,hi_r,hi_c);
    backtrace_sw_heap(m,n,hi_r,hi_c,la_table);
    free(la_table);
}

/* **************************************************** */

void backtrace_nw(int m, int n, int * ga_table){
    int i=m-1, j=n-1; //decrement for indexing
    int length = ((m>n)?m:n)-1; //longer of two sequences
//    printf("%d @ [%d][%d]\n",ga_table[i][j],i,j);
    int edits=0;
    enum flag nw_flag;
    int temp_max = -32766;
    while(i>0 || j>0){
        temp_max=-32766; //some very low number
        //check left
        if(j>0 && access(i,j-1,n,ga_table)>temp_max){
            temp_max = access(i,j-1,n,ga_table);
            nw_flag = left;
        }
        //check up
        if(i > 0 && access(i-1,j,n,ga_table) > temp_max){
            temp_max = access(i-1,j,n,ga_table);
            nw_flag = up;
        }
        //check diagnoal
        if(i > 0 && j > 0 && access(i-1,j-1,n,ga_table) >= temp_max){
            temp_max = access(i-1,j-1,n,ga_table);
            nw_flag = diagonal;
        }
        //update edits & positions
        if(nw_flag == up){
            i-=1;
            edits += gap;
//            printf("GAP_up\n");
        }
        else if(nw_flag == left){
            j-=1;
            edits += gap;
//            printf("GAP_left\n");
        }
        else{
            i-=1;
            j-=1;
            if(text[i]!=text[m+j]){
                edits++; //-= mismatch;
//                printf("MISMATCH: %d!=%d\n",text[i],text[m+j]);
            }
        }
//        printf("%d @ [%d][%d]\n",temp_max,i,j);
    }

    printf("%d,%d;",length,edits);
    fflush(stdout);
/*
    if((float)edits/(float)length < best_score){
        best_length = length;
        best_edits = edits;
        best_score = (float)edits/(float)length;
//printf("\nUPDATE: best_score = %lf\n",best_score);
    }
*/
}

void nw_heap(int m, int n){
    m++; n++;
    int * ga_table = malloc(m * n * (sizeof(int)));
    //populate DP table
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            //0th row and col should all be 0's
            if(j==0){*access_w(i,j,n,ga_table) = -i * gap;}
            else if(i==0){*access_w(i,j,n,ga_table) = -j * gap;}
            else{
                //match
                if(text[i-1] == text[m+j-1]){
//                    printf("%d == %d\n",text[i-1],text[m+j-1]);
                    *access_w(i,j,n,ga_table)=access(i-1,j-1,n,ga_table) + match;
                }
                //mismatch
                else{
                *access_w(i,j,n,ga_table) = max3(access(i-1,j,n,ga_table)-gap,
                            access(i,j-1,n,ga_table)-gap,access(i-1,j-1,n,ga_table)+mismatch);
//              printf("%d!=%d\n",text[i-1],text[m+j-1]);
                }
            }
        }
    }
    //print_table(m,n,ga_table);
    //printf("hi_val=%d @ [%d][%d]\n",hi_val,hi_r,hi_c);
    backtrace_nw(m,n,ga_table);
    free(ga_table);
}
