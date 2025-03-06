#include "main.h"

void text::undo(char opr){
    //pop the tail make changes
    struct str *temp;
    if(opr==UNDO){
        temp=Undo.tail;
        if(!temp)  return;
    }
    else{
        temp=Redo.tail;
        if(!temp)  return;
        temp->type=!temp->type;
    }
    if(temp->type==ADD){                            //if the change was insert, delete the characters
        move_to(temp->line, temp->col);
        for(int i=0;i<temp->data.size();i++){
            if(temp->data[i]=='\n'){
                Cursorline=Cursorline->next;
                Cursor=Cursorline->head;
                cursor_line++;
                cursor_col=0;
                delete_before(NOLOG);
            }
            else{
                delete_after(NOLOG);
            }
        }
    }
    else{                                           //if the change was delete, insert the characters
        move_to(temp->line, temp->col);
        for(int i=0;i<temp->data.size();i++){
            if(temp->data[i]=='\n'){
                move_to(cursor_line, cursor_col+1);
            }
            insert_before(temp->data[i],NOLOG);
        }
    }
    if(temp->prev){
        temp->prev->next=NULL;
    }
    else{
        if(opr==UNDO){
            Undo.head=NULL;
        }
        else{
            Redo.head=NULL;
        }
    }
    if(opr==UNDO){
        Undo.tail=temp->prev;
        //push the change to the redo stack
        push_to_redo(temp);
    }
    else{
        Redo.tail=temp->prev;
        //push the change to the undo stack
        temp->type=!temp->type;
        push_to_undo(temp);
    }
    
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

void text::push_to_undo(struct str* node){
    if(Undo.head){
        Undo.tail->next=node;
        node->prev=Undo.tail;
    }
    else{
        Undo.head=node;
        node->prev=NULL;
    }
    Undo.tail=node;
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
                if(temp->line==cursor_line&&(temp->col-1==cursor_col||temp->col==cursor_col)&&(ch!=' '||temp->data[0]==' ')&&temp->data.size()<15){
                    if(temp->col-1==cursor_col){
                        temp->data.insert(temp->data.begin(),ch);
                        temp->col=cursor_col;
                    }
                    else{
                        if(temp->data.compare("\n")){
                            temp->data.push_back(ch);
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

void text::insert_line_undo(){
    struct str *temp=new str;
    if(Undo.tail){
        Undo.tail->next=temp;
        temp->prev=Undo.tail;
        Undo.tail=temp;
    }
    else{
        Undo.head=Undo.tail=temp;
    }
    temp->col=0;
    temp->line=cursor_line;
    temp->type=DELETE;
    struct charn *temp1=Cursorline->head;
    while(temp1){
        temp->data.push_back(temp1->data);
        temp1=temp1->next;
    }
}