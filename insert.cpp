#include "insert.h"
#include "main.h"
#include "edit.h"
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
}

void delete_before(text &t){
    struct charn *temp=t.Cursor->prev;
    struct line *temp1=t.Cursorline->prev;
    if(temp){         //delete the prev element
        if((temp=t.Cursor->prev->prev)){
            temp->next=t.Cursor;
            temp=t.Cursor->prev;
            t.Cursor->prev=temp->prev;
        }
        else{
            temp=t.Cursorline->head;
            t.Cursorline->head=temp->next;
            t.Cursorline->head->prev=NULL;
        }
        delete temp;
        t.cursor_col--;
    }
    else if(temp1){        //move to the prev line
        temp=temp1->tail;
        t.cursor_col=len(temp1)-1;
        temp1->tail=temp->prev;
        temp1->tail->next=t.Cursorline->head;
        t.Cursorline->head->prev=temp1->tail;
        temp1->tail=t.Cursorline->tail;
        temp1->next=t.Cursorline->next;
        t.Cursorline->next->prev=temp1;
        temp1=t.Cursorline;
        t.Cursorline=t.Cursorline->prev;
        t.cursor_line--;
        t.line_count--;
        delete temp;
        delete temp1;
    }  
}

void delete_after(text& t){
    struct charn* temp=t.Cursor;
    if(t.Cursor->data!='\n'){
        t.Cursor=t.Cursor->next;
        delete_before(t);
        t.cursor_col++;
        t.Cursor=temp;
    }
    else{
        unsigned int temp1=t.cursor_col;
        t.Cursorline=t.Cursorline->next;
        t.Cursor=t.Cursorline->head;
        t.cursor_line++;
        delete_before(t);
        t.cursor_col=temp1;
    }
}