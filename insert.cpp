#include "main.h"
#include <iostream>

void insert_before(char data,text& t){

    if(data=='\n'){
        struct line *new1=new line;
        struct charn *new2=new charn;
        if(new1==NULL||new2==NULL) {
            std::cout<<"Memory allocation failure"<<std::endl;
            return;
        }
        new2->next=NULL;
        new2->data=data;
        if(t.prev){
            new1->next=t.prev->next->next;new1->prev=t.prev->next;
            new2->prev=t.Cursor->prev;
            if(t.Cursor->prev){
                t.Cursor->prev->next=new2;
                t.Cursor->prev=NULL;
            }
            else{
                t.prev->next->head=new2;
            }
            new1->tail=t.prev->next->tail;
            t.prev->next->tail=new2;
            t.prev->next->next=new1;
            new1->head=t.Cursor;
            t.prev_line_len=t.cursor_col=0;
            t.prev=t.prev->next;
        }
        else{
            new1->next=t.head;
            t.head=new1;
            new1->prev=NULL;
            if(t.tail==NULL){
                t.tail=new1;
            }
            new2->prev=NULL;
            new1->head=new1->tail=new2;
            t.prev=t.head;
            t.prev->next->prev=t.head;
        }
        t.cursor_line++;
        t.line_count++;
    }
    else{
        std::cout<<std::endl;
    }
}