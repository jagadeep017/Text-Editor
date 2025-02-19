#include "main.h"

void text::undo(){
    //pop the tail make changes
    struct str *temp=Undo.tail;
    if(!Undo.tail)  return;
    move_to(temp->line, temp->col);
    for(int i=0;i<temp->data.size();i++){
        delete_after();
    }
    if(temp->prev){
        temp->prev->next=NULL;
    }
    else{
        Undo.head=NULL;
    }
    Undo.tail=temp->prev;

    //push the change to the redo stack
    push_to_redo(temp);
}

void text::redo(){
    //pop the tail make changes and push that to undo stack
}

void text::push_to_redo(struct str* node){
    if(Redo.head){
        Redo.tail->next=node;
        node->prev=Redo.tail;
    }
    else{
        Redo.head=node;
        node->prev=NULL;
    }
    Redo.tail=node;
}

void text::insert_undo(char ch){
    struct str* temp;
    if(Undo.head){
        temp=Undo.tail;
        if(temp->line==cursor_line&&temp->col+temp->data.size()==cursor_col&&ch!=' '&&temp->data.size()<30){
            temp->data.push_back(ch);
        }
        else{
            temp=new str;
            Undo.tail->next=temp;
            temp->prev=Undo.tail;
            Undo.tail=temp;
            temp->data.push_back(ch);
            temp->line=cursor_line;
            temp->col=cursor_col;
            temp->type=ADD;
        }
    }
    else{
        temp=new str;
        Undo.head=Undo.tail=temp;
        temp->data.push_back(ch);
        temp->line=cursor_line;
        temp->col=cursor_col;
        temp->type=ADD;
    }

}
