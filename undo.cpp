#include "main.h"

void text::undo(){

}

void text::redo(){

}

void text::insert_undo(char ch){
    struct str* temp;
    if(Undo.head){
        temp=Undo.tail;
        if(temp->Line==Cursorline&&temp->col+temp->data.size()==cursor_col){
            temp->data.push_back(ch);
        }
        else{
            temp=new str;
            Undo.tail->next=temp;
            temp->prev=Undo.tail;
            Undo.tail=temp;
            temp->data.push_back(ch);
            temp->Line=Cursorline;
            temp->col=cursor_col;
            temp->type=ADD;
        }
    }
    else{
        temp=new str;
        Undo.head=Undo.tail=temp;
        temp->data.push_back(ch);
        temp->Line=Cursorline;
        temp->col=cursor_col;
        temp->type=ADD;
    }

}
