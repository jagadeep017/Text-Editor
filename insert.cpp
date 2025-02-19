#include "main.h"
#include <iostream>

//inserts the character before the cursor
void text::insert_before(char data){
    insert_undo(data);
    struct charn *new2=new charn;
    if(new2==NULL) {
        std::cout<<"Memory allocation failure"<<std::endl;
        return;
    }
    new2->next=NULL;
    new2->data=data;
    if(data=='\n'){                             //inserting a new line(\n)
        struct line *new1=new line;
        if(new1==NULL) {
            std::cout<<"Memory allocation failure"<<std::endl;
            return;
        }
        if(Cursorline){
            new1->next=Cursorline->next;new1->prev=Cursorline;
            new2->prev=Cursor->prev;
            if(Cursor->prev){
                Cursor->prev->next=new2;
                Cursor->prev=NULL;
            }
            else{
                Cursorline->head=new2;
            }
            new1->tail=Cursorline->tail;
            Cursorline->tail=new2;
            Cursorline->next=new1;
            new1->head=Cursor;
            cursor_col=0;
            Cursorline=Cursorline->next;
        }
        cursor_line++;
        line_count++;
    }
    else if(data){
        new2->next=Cursor;
        new2->prev=Cursor->prev;
        if(Cursor->prev){
            Cursor->prev->next=new2;
        }
        else{
            Cursorline->head=new2;
        }
        Cursor->prev=new2;
        cursor_col++;
    }
}

//inserts the character the cursor is pointing to
void text::delete_before(){
    struct charn *temp=Cursor->prev;
    struct line *temp1=Cursorline->prev;
    if(temp){         //delete the prev element
        if((temp=Cursor->prev->prev)){
            temp->next=Cursor;
            temp=Cursor->prev;
            Cursor->prev=temp->prev;
        }
        else{
            temp=Cursorline->head;
            Cursorline->head=temp->next;
            Cursorline->head->prev=NULL;
        }
        cursor_col--;
    }
    else if(temp1){        //if cursor is at the start of the line move to the prev line
        temp=temp1->tail;
        if(temp->prev){
            cursor_col=len(temp1)-1;
            temp1->tail=temp->prev;
            temp1->tail->next=Cursorline->head;
            Cursorline->head->prev=temp1->tail;
        }
        else{
            temp1->head=Cursor;
            cursor_col=0;
        }
        temp1->tail=Cursorline->tail;
        temp1->next=Cursorline->next;
        if(Cursorline->next){
            Cursorline->next->prev=temp1;
        }
        else{
            tail=temp1;
        }
        temp1=Cursorline;
        Cursorline=Cursorline->prev;
        cursor_line--;
        line_count--;
        delete temp1;
    }
    delete temp;
}

//deletes the character after the cursor
void text::delete_after(){
    if(Cursor->data!='\n'){
        Cursor=Cursor->next;
        delete_before();
        cursor_col++;
    }
    else if(Cursor->prev){
        delete_before();
    }
}

//deletes the current line
void text::delete_line(){
    if(!line_count) return;
    struct line *temp=Cursorline;
    if(Cursorline->next){
        move_to(cursor_line+1, cursor_col);
        Cursorline->prev=temp->prev;
        if(temp==head){
            head=Cursorline;
        }
        else{
            temp->prev->next=Cursorline;
        }
    }
    else{
        move_to(cursor_line-1,cursor_col);
        Cursorline->next=NULL;
        tail=Cursorline;
    }
    line_count--;
    struct charn *temp1=temp->head;
    while(temp1->next){
        temp1=temp1->next;
        delete temp1->prev;
    }
    delete temp1;
    delete temp;
}

//pushes a char into the command string
void text::insert_cmd(char ch){
    command.push_back(ch);
}

//baskspace for commands
void text::pop_ch_cmd(){
    if(command.length()>1){
        command.pop_back();
    }
}