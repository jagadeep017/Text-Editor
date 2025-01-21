#include "main.h"
#include "edit.h"
#include <stdio.h>

void move_cursor(int pos,text& t){
    unsigned int temp;
    if(pos<0){
        while(pos&&t.cursor_line){
            t.cursor_line--;
            t.Cursorline=t.Cursorline->prev;
            pos++;
        }
    }
    else{
        if(pos+t.cursor_line>=t.line_count) return;
        while(pos&&t.cursor_line<t.line_count){
            t.cursor_line++;
            t.Cursorline=t.Cursorline->next;
            pos--;
        }
    }
    temp=len(t.Cursorline);
    
    if(t.prev_cursor_col){
        if(t.prev_cursor_col+1>temp){
            t.cursor_col=temp-1;
        }
        else{
            t.cursor_col=t.prev_cursor_col;
        }
    }
    else{
        t.prev_cursor_col=t.cursor_col;
        if(t.cursor_col+1>temp){
            t.cursor_col=temp-1;
        }
    }
}

void move_cursor_side(int pos,text& t){
    if(pos<0){
        while(pos&&t.Cursor){
            t.Cursor=t.Cursor->prev;
            if(t.Cursor==NULL){
                if(t.Cursorline->prev==NULL);
                else{
                    t.cursor_line--;
                    t.Cursor=t.Cursorline->prev->tail;
                    t.cursor_col=len(t.Cursorline->prev)-1;
                    t.Cursorline=t.Cursorline->prev;
                }
            }
            else{
                t.cursor_col--;
            }
            pos++;
        }
    }
    else{
        while(pos&&t.Cursor){
            t.Cursor=t.Cursor->next;
            if(t.Cursor==NULL&&t.Cursorline->next==NULL) return;
            if(t.Cursor==NULL){
                t.cursor_line++;
                t.Cursor=t.Cursorline->next->head;
                t.Cursorline=t.Cursorline->next;
                t.cursor_col=0;
            }
            else{
                t.cursor_col++;
            }
            pos--;
        }
    }
    t.prev_cursor_col=0;
}

unsigned int len(struct line * head){
    unsigned int res=0;
    struct charn *temp=head->head;
    while(temp){
        res++;
        temp=temp->next;
    }
    return res;
}