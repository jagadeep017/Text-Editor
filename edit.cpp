#include "main.h"

void move_cursor(int pos,text& t){
    if(pos<0&&t.line<=-pos){    
        t.line=0;
        return;
    }
    else{
        t.line+=pos;
    }
}

void move_cursor_side(int pos,text& t){
    if(pos<0&&t.Cursor<=-pos){    
        t.Cursor=0;
        return;
    }
    else{
        t.Cursor+=pos;
    }
}