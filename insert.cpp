#include "main.h"
#include <iostream>

void insert_before(char data,text& t){

    if(data=='\n'){
        struct line *new1=new line;
        new1->next=t.prev->next->next;new1->prev=t.prev->next;
        struct charn *new2=new charn;
        new2->next=NULL;
        new2->data=data;
        t.Cursor->prev->next=new2;
        new2->prev=t.Cursor->prev;
        new1->tail=t.prev->next->tail;
        t.prev->next->tail=new2;
        t.prev->next->next=new1;
        t.Cursor->prev=NULL;
        new1->head=t.Cursor;
        t.cursor_line++;
        t.line_count++;
        t.prev_line_len=t.cursor_col=0;
        t.prev=t.prev->next;
    }
    else{
        std::cout<<std::endl;
    }
}