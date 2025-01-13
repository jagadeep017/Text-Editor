#include "main.h"

void move_cursor(int pos,text& t){
    if((pos<0&&!t.prev)||(pos>0&&t.atend))  return;
    else if(pos<0){
        if(t.prev_cursor_col==0){
            if(t.cursor_col>t.prev_line_len){
                if(t.cursor>t.cursor_col+1){
                    t.cursor-=(t.cursor_col+1);
                }
                else{
                    t.cursor=0;
                }
            }
            else{
                if(t.cursor>t.prev_line_len+1){
                    t.cursor-=t.prev_line_len+1;
                }
                else{
                    t.cursor=0;
                }
            }
        }
        else{
            if(t.prev_cursor_col>t.prev_line_len){
                t.cursor-=(t.cursor_col+1);
            }
            else{
                t.cursor-=(t.cursor_col+t.prev_line_len-t.prev_cursor_col+1);
            }
        }
    }
    else{
        struct charn *temp=t.Cursor;
        unsigned int length=0;
        while(temp&&temp->data!='\n'&&temp->data!=-1){
            temp=temp->next;
            t.cursor++;
        }
        if(temp){
            temp=temp->next;
        }
        while(temp&&temp->data!='\n'&&temp->data!=-1){
            temp=temp->next;
            length++;
        }
        if(t.prev_cursor_col){
            if(length>t.prev_cursor_col){
                t.cursor+=t.prev_cursor_col+1;
            }
            else{
                t.cursor+=length+1;
            }
        }
        else{
            if(length>t.cursor_col){
                t.cursor+=t.cursor_col+1;
            }
            else{
                t.cursor+=length+1;
            }
        }
    }
    if(t.prev_cursor_col==0){
        t.prev_cursor_col=t.cursor_col;
    }
}

void move_cursor_side(int pos,text& t){
    if(pos<0&&t.cursor<=-pos){
        t.prev_cursor_col=0;
        t.cursor=0;
    }
    else{
        if(t.atend!=2||pos<0){
            t.prev_cursor_col=0;
            t.cursor+=pos;
        }
    }
}