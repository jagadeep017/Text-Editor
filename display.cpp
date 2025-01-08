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
    //char prev='\0';
    while (temp!=NULL&&temp->data!=EOF) {
        if(line_count==t.line&&char_count==t.Cursor){
            if(temp->data=='\n'){
                std::cout<<"\033[47m"<<' '<<temp->data<<"\033[0m";
            }
            else{
                std::cout<<"\033[47m"<<temp->data<<"\033[0m";
            }
        }
        else{
            std::cout<<temp->data;
        }
        if (temp->data=='\n') {
            line_count++;
            char_count=0;
        }
        else{
            char_count++;
        }
        temp=temp->next;
    }
    std::cout<<std::endl;
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
    if(*head==NULL){
        *head=new1;
        *tail=new1;
    }
    else{
        (*tail)->next=new1;
        *tail=new1;
    }
}