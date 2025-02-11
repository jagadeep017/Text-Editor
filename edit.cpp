#include "main.h"
#include <stdio.h>

//moves the cursor up or down for pos(int) numbers of lines
void text::move_cursor(int pos){
    unsigned int temp;
    if(pos<0){                                                  //move up
        while(pos&&cursor_line){
            cursor_line--;
            Cursorline=Cursorline->prev;
            pos++;
        }
    }
    else{                                                       //move down
        if(pos+cursor_line>=line_count) return;
        while(pos&&cursor_line<line_count){
            cursor_line++;
            Cursorline=Cursorline->next;
            pos--;
        }
    }
    temp=len(Cursorline);
    
    if(prev_cursor_col){                                        //setting the cursor based on prev_cursor_col and cursor_col
        if(prev_cursor_col+1>temp){
            cursor_col=temp-1;
        }
        else{
            cursor_col=prev_cursor_col;
        }
    }
    else{
        prev_cursor_col=cursor_col;
        if(cursor_col+1>temp){
            cursor_col=temp-1;
        }
    }
    Cursor=Cursorline->head;
    for(int i=0;i<cursor_col;i++){
        Cursor=Cursor->next;                                    //move to the cursor to the correct position
    }
}

//moves the cursor left or right for pos(int) number of characters
//can jump to the next line or prev line if the cursor is at the end or start of the line
void text::move_cursor_side(int pos){
    if(pos<0){                                                  //move left
        if(!Cursor->prev&&!Cursorline->prev) return;            //if the cursor is at the start of the file
        while(pos&&Cursor){
            Cursor=Cursor->prev;
            if(Cursor==NULL){                                   //if the cursor is at the start of the line
                if(Cursorline->prev){
                    cursor_line--;
                    Cursor=Cursorline->prev->tail;
                    cursor_col=len(Cursorline->prev)-1;
                    Cursorline=Cursorline->prev;
                }
            }
            else{
                cursor_col--;
            }
            pos++;
        }
    }
    else{                                                       //move right
        if(!Cursor->next&&!Cursorline->next) return;            //if the cursor is at the end of the file
        while(pos&&Cursor){
            Cursor=Cursor->next;
            if(Cursor==NULL&&Cursorline->next==NULL) return;
            if(Cursor==NULL){                                   //if the cursor is at the end of the line
                cursor_line++;
                Cursor=Cursorline->next->head;
                Cursorline=Cursorline->next;
                cursor_col=0;
            }
            else{
                cursor_col++;
            }
            pos--;
        }
    }
    prev_cursor_col=0;                                          //reset the prev_cursor_col
}

//returns the length of the line
unsigned int text::len(struct line * head){
    unsigned int res=0;
    struct charn *temp=head->head;
    while(temp){
        res++;
        temp=temp->next;
    }
    return res;
}