#include "main.h"
#include "edit.h"
#include <stdio.h>

void move_cursor(int pos,text& t){
    unsigned int temp;
    if(pos<0){
        while(pos&&t.cursor_line){
            t.cursor_line--;
            t.prev=t.prev->prev;
            pos++;
        }
    }
    else{
        if(pos+t.cursor_line>=t.line_count) return;
        while(pos&&t.cursor_line<t.line_count){
            t.cursor_line++;
            if(t.prev){
                t.prev=t.prev->next;
            }
            else{
                t.prev=t.head;
            }
            pos--;
        }
    }
    if(t.prev){
        temp=len(t.prev->next);
    }
    else{
        temp=len(t.head);
    }
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
        //struct charn *temp=t.Cursor;
        while(pos&&t.Cursor){
            t.Cursor=t.Cursor->prev;
            if(t.Cursor==NULL){
                if(t.prev==NULL);
                else{
                    t.cursor_line--;
                    t.Cursor=t.prev->tail;
                    t.cursor_col=len(t.prev)-1;
                    t.prev=t.prev->prev;
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
            if(t.Cursor==NULL&&t.prev&&t.prev->next->next==NULL) return;
            if(t.Cursor==NULL){
                t.cursor_line++;
                if(t.prev){
                    t.Cursor=t.prev->next->next->head;
                    t.prev=t.prev->next;
                }
                else{
                    t.Cursor=t.head->next->head;
                    t.prev=t.head;
                }
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