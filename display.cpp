#include "main.h"
#include "display.h"
#include <cstring>
#include <stdlib.h> 
#include <iostream>
#include <fstream>

void display(unsigned short int row,unsigned short int col,text& t){
    t.prev=NULL;
    t.prev_line_len=0;
    system("clear");    //clear the screen
    struct charn *temp=t.head;
    unsigned int line_count=0,char_count=0;
    unsigned int courser_line=0,courser_col=0;
    char flag=1;
    while (temp!=NULL&&temp->data!=EOF) {
        if(char_count==t.cursor){
            t.Cursor=temp;
            if(temp->data=='\n'){
                if(line_count==row-3){
                    t.atend=1;
                }
                std::cout<<"\033[47m"<<' '<<"\033[0m"<<temp->data;
            }
            else{
                std::cout<<"\033[47m"<<temp->data<<"\033[0m";
            }
            flag=0;
            courser_line=line_count;
        }
        else{
            std::cout<<temp->data;
        }
        if (temp->data=='\n') {
            line_count++;
            if(flag){
                t.prev_line_len=courser_col;
                t.prev=temp;
                courser_col=0;
            }
        }
        else if(flag){
            courser_col++;
        }
        char_count++;
        temp=temp->next;
        if(line_count==row-2){
            break;
        }
        if(courser_col==col){
            line_count++;
            courser_col=0;
        }
    }
    t.cursor_col=courser_col;
    if(courser_line==line_count-1){
        t.atend++;
    }
    else{
        t.atend=0;
    }
    std::cout<<"Ln "<<courser_line+1<<", Col "<<courser_col+1<<std::endl;
}

void add_data(char* name,struct charn **head,struct charn **tail){
    char *temp=strstr(name,".");
    if(temp==NULL){
        std::cout<<"Invalid file name"<<std::endl;
        exit(0);
    }
    if(strcmp(temp,".txt")!=0 && strcmp(temp,".c")!=0 && strcmp(temp,".cpp")!=0 && strcmp(temp,".h")!=0){
        std::cout<<"Invalid file type"<<std::endl;
        exit(0);
    }
    std::ifstream file(name);
    if(!file.is_open()){
        std::cout<<"File "<<name<<" not found"<<std::endl;
        exit(0);
    }
    while(!file.eof()){
        char ch=file.get();
        if(ch!='\r')
            insert_last(ch,head,tail);
    }
    file.close();
}

void insert_last(char c,struct charn **head,struct charn **tail){
    struct charn *new1=new charn;
    if(new1==NULL){
        std::cout<<"Memory allocation failed"<<std::endl;
        exit(0);
    }
    new1->data=c;
    new1->next=NULL;
    new1->prev=NULL;
    if(*head==NULL){
        *head=new1;
        *tail=new1;
    }
    else{
        (*tail)->next=new1;
        new1->prev=*tail;
        *tail=new1;
    }
}