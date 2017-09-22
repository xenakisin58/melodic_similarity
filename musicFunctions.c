#include <stdio.h>

char * note_names[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
char * dur_names[] = {"1/32","1/16","1/8","1/4","1/2","1","2/1","4/1"};

int transpose(int k1, int k2){
    int temp;
    if(k1 >=12 && k2 < 12){ //min vs. maj
        temp = ((12-(k2-k1))%12)+3;
        if(temp<0){temp+=12;}
        return temp;
    }
    else if(k1 <12 && k2 >=12){ //maj vs. min
        temp = ((12-(k2-k1))%12)+9;
        if(temp<0){temp+=12;}
        return temp;
    }
    else{
        temp = (12-(k2-k1))%12;
        if(temp<0){temp+=12;}
        return temp;
    }
}

int nint2(float x)
{
  if( x >= 0.0 )
    {
      return (int)((x)+(0.5));
    }
  else
    {
      return (int)((x)-(0.5));
    }
}

int quantize(int val, int tpb, int met){
    float temp = ((float)val/(tpb * met))*32;
//    printf("\n--%lf--\n",temp);
    if(temp>127){temp=127;}
//    printf("%d @ %d * %d = %lf = %d\n",val,tpb,met,temp,nint2(temp));
    return nint2(temp);
}

int encode(int val, int dur){
    return dur + (val * 128);
}

int decodeDur(int enc_val){
    return enc_val % 128;
}

int decodeNote(int enc_val){
    return enc_val / 128;
}

void printEnc(int enc_val){
    printf("%s%d,%d",note_names[(enc_val/128)%12],(enc_val/128),decodeDur(enc_val));
}

int interval(int curr, int next){
    return next - curr;
}

int intervalMod(int curr, int next){
    return (next - curr)%12;
}

int parsons(int curr, int next){
    if(curr == next){return 1;}
    else if(curr > next){return 0;}
    else{return 2;}
}
