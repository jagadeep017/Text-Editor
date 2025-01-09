#include "main.h"

void move_cursor(int pos,text& t){
   
}

void move_cursor_side(int pos,text& t,int max){
    if(pos<0&&t.cursor<=-pos){
        t.cursor=0;
    }
    else{
        t.cursor+=pos;
    }
}