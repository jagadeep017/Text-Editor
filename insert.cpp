#include "main.h"
#include <iostream>

void insert_before(char data,text& t){
    
    struct charn *new2=new charn;
    if(new2==NULL) {
        std::cout<<"Memory allocation failure"<<std::endl;
        return;
    }
    new2->next=NULL;
    new2->data=data;
    if(data=='\n'){
        struct line *new1=new line;
        if(new1==NULL) {
            std::cout<<"Memory allocation failure"<<std::endl;
            return;
        }
        if(t.Cursorline){
            new1->next=t.Cursorline->next;new1->prev=t.Cursorline;
            new2->prev=t.Cursor->prev;
            if(t.Cursor->prev){
                t.Cursor->prev->next=new2;
                t.Cursor->prev=NULL;
            }
            else{
                t.Cursorline->head=new2;
            }
            new1->tail=t.Cursorline->tail;
            t.Cursorline->tail=new2;
            t.Cursorline->next=new1;
            new1->head=t.Cursor;
            t.prev_line_len=t.cursor_col=0;
            t.Cursorline=t.Cursorline->next;
        }
        t.cursor_line++;
        t.line_count++;
    }
    else if(data){
        new2->next=t.Cursor;
        new2->prev=t.Cursor->prev;
        if(t.Cursor->prev){
            t.Cursor->prev->next=new2;
        }
        else{
            t.Cursorline->head=new2;
        }
        t.Cursor->prev=new2;
        t.cursor_col++;
    }
    else{
        std::cout<<std::endl;
    }
}