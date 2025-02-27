#include "main.h"

void text::undo(){
    //pop the tail make changes
    struct str *temp=Undo.tail;
    if(!temp)  return;
    if(temp->type==ADD){                            //if the change was insert, delete the characters
        move_to(temp->line, temp->col);
        for(int i=0;i<temp->data.size();i++){
            if(temp->data[i]=='\n'){
                Cursorline=Cursorline->next;
                Cursor=Cursorline->head;
                cursor_line++;
                cursor_col=0;
                delete_before(0);
            }
            else{
                delete_after(0);
            }
        }
        if(temp->prev){
            temp->prev->next=NULL;
        }
        else{
            Undo.head=NULL;
        }
        Undo.tail=temp->prev;
    }
    else{                                           //if the change was delete, insert the characters
        if(temp->data.compare("\n")==0){
            temp->col++;
        }
        move_to(temp->line, temp->col-1);
        for(int i=0;i<temp->data.size();i++){
            if(temp->data[i]=='\n'){
                insert_before('\n',0);
            }
            else{
                insert_before(temp->data[i],0);
            }
        }
        if(temp->prev){
            temp->prev->next=NULL;
        }
        else{
            Undo.head=NULL;
        }
        Undo.tail=temp->prev;
        
    }
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

void text::insert_undo(char ch,unsigned char type){
    struct str* temp;
    char flag=0;
    if(Undo.tail){
        temp=Undo.tail;
        if(temp->type==type){
            if(type==ADD){
                if(temp->line==cursor_line&&temp->col+temp->data.size()==cursor_col&&ch!=' '&&temp->data.size()<20){
                    temp->data.push_back(ch);
                }
                else{
                    flag=1;
                }
            }
            else{
                if(temp->line==cursor_line&&temp->col-1==cursor_col&&ch!=' '&&temp->data.size()<15){
                    temp->data.insert(temp->data.begin(),ch);
                    temp->col=cursor_col;
                }
                else{
                    flag=1;
                }
            }
        }
        else{
            flag=1;
        }
    }
    else{
        temp=new str;
        Undo.head=Undo.tail=temp;
        temp->data.push_back(ch);
        temp->line=cursor_line;
        temp->col=cursor_col;
        temp->type=type;
    }
    if(flag){
        temp=new str;
        Undo.tail->next=temp;
        temp->prev=Undo.tail;
        Undo.tail=temp;
        temp->data.push_back(ch);
        temp->line=cursor_line;
        temp->col=cursor_col;
        temp->type=type;
    }
}
