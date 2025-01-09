#include "main.h"
#include "display.h"
#include <cstring>
#include <stdlib.h> 
#include <iostream>
#include <fstream>

void display(int row,int col,text& t){
    system("clear");    //clear the screen
    struct charn *temp=t.head;
    unsigned int line_count=0,char_count=0;
    unsigned int courser_line=0,courser_col=0;
    char flag=1;
    while (temp!=NULL&&temp->data!=EOF) {
        if(char_count==t.cursor){
            if(temp->data=='\n'){
                t.atend=1;
                std::cout<<"\033[47m"<<' '<<"\033[0m"<<temp->data;
            }
            else{
                t.atend=0;
                std::cout<<"\033[47m"<<temp->data<<"\033[0m";
            }
            flag=0;
            courser_line=line_count;
            // if(temp->data=='\n'&&flag){
            //     t.atend=1;
            //     std::cout<<"\033[47m"<<' '<<temp->data<<"\033[0m";
            // }
            // else if(char_count==t.Cursor){
            //     if(temp->data=='\n'){
            //         t.atend=1;
            //     }
            //     else{
            //         t.atend=0;
            //     }
            //     std::cout<<"\033[47m"<<temp->data<<"\033[0m";
            //     flag=0;
            // }
            // else{
            //     if(temp->data=='\n'&&temp->prev->data=='\n'&&t.Cursor>0&&flag){
            //         move_cursor_side(col,t,col);
            //         t.Cursor=0;
            //     }
            //     std::cout<<temp->data;
            // }
        }
        else{
            std::cout<<temp->data;
        }
        if (temp->data=='\n') {
            //flag=1;
            line_count++;
            if(flag){
                courser_col=0;
            }
        }
        else{
            char_count++;
            if(flag){
                courser_col++;
            }
        }
        temp=temp->next;
        if(line_count==row-2){
            break;
        }
        // if(char_count==col-1){
        //     while(temp->data!='\n'){
        //         temp=temp->next;
        //     }
        //     continue;
        // }
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