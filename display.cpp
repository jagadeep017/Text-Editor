#include "main.h"
#include "display.h"
#include <curses.h>


void display(unsigned short int row,unsigned short int col,text& t){
    t.atend=0;
    clear();        //clear the screen
    struct line *temp=t.head;
    unsigned int line_count=0,char_count=0;
    unsigned int courser_line=0,courser_col=0;
    unsigned short temp1=0;
    unsigned int offset=0;
    
    if(t.line_offset+t.cursor_line>=row-4){
        offset=t.cursor_line+4-row;
    }
    line_count=t.line_count;
    while(line_count){
        temp1++;
        line_count/=10;
    }
    line_count=offset;
    while(line_count){
        temp=temp->next;
        line_count--;
    }
    line_count=offset;
    while (temp!=NULL) {
        char_count=0;
        struct charn *temp2=temp->head;
        // std::cout<<"\033[36m"<<std::setw(temp1)<<line_count+1<<' '<<"\033[0m";
        printw("%d ",line_count+1);
        while(temp2&&temp2->data!=EOF){
            if(line_count==t.cursor_line&&char_count==t.cursor_col){
                if(temp2->data=='\n'){
                    if(line_count==row-1){
                        t.atend=1;
                    }
                    // std::cout<<"\033[47m"<<' '<<"\033[0m"<<temp2->data;
                    printw("|%c",temp2->data);
                }
                else{
                    // std::cout<<"\033[47m"<<temp2->data<<"\033[0m";
                    printw("%c|",temp2->data);
                }
                t.Cursorline=temp;
                t.Cursor=temp2;
            }
            else{
                // std::cout<<temp2->data;
                printw("%c",temp2->data);
            }
            char_count++;
            temp2=temp2->next;
            if(char_count+temp1+1==col){
                // std::cout<<std::setw(temp1+1)<<' ';
                printw(" ");
            }
        }
        temp=temp->next;
        line_count++;
        if(line_count-offset==row-1){
            break;
        }
    }
    if(courser_line==line_count-1){
        t.atend++;
    }
    if(t.line_count<row-1){
        temp1=row-1-t.line_count;
    }
    else if(t.cursor_line+3>t.line_count){
        temp1=t.cursor_line+3-t.line_count;
    }
    else{
        temp1=0;
    }
    while(temp1>0){
        // std::cout<<"\033[36m"<<'~'<<std::endl;
        printw("~\n");
        temp1--;
    }
    // std::cout<<"\033[36m"<<std::setw(col-20)<<"Ln "<<t.cursor_line+1<<", Col "<<t.cursor_col+1<<", ";
    if(t.mode==INSERT){
        printw("--INSERT MODE-- \t\t\t\t");
    }
    else{
        printw("\t\t\t\t\t\t");
    }
    printw("Ln %d, Col %d, ",t.cursor_line+1,t.cursor_col+1);
    if(offset==0){
        // std::cout<<"TOP";
        printw("TOP");
    }
    else if(t.line_count<row-1||t.cursor_line+3>t.line_count){
        // std::cout<<"BOT";
        printw("BOT");
    }
    else{
        // std::cout<<(t.cursor_line*100)/t.line_count<<"%";
        printw("%d%%  %d",(t.cursor_line*100)/t.line_count,t.Cursor->data);
    }
    // std::cout<<"\033[0m"<<'\r';
    t.line_offset=offset;
    line_count=t.cursor_line+1;
    while(line_count){
        temp1++;
        line_count/=10;
    }
    move(t.cursor_line-offset, t.cursor_col+temp1+1); 
}
