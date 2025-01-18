#include "main.h"
#include "file.h"
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <stdlib.h> 
#include <iostream>
#include <fstream>


void add_data(char* name,struct line **head,struct line **tail,unsigned int *lines){
    char *temp=strstr(name,".");
    if(temp==NULL){
        std::cout<<"Invalid file name"<<std::endl;
        exit(0);
    }
    if(strcmp(temp,".txt")!=0 && strcmp(temp,".c")!=0 && strcmp(temp,".cpp")!=0 && strcmp(temp,".h")!=0){
        std::cout<<"Invalid file type"<<std::endl;
        exit(0);
    }
    std::ifstream file;
    file.open(name);
    if(!file.is_open()){
        std::cout<<"File "<<name<<" not found"<<std::endl;
        exit(0);
    }
    struct line* temp1=*head;
    while(!file.eof()){
        struct line* new1=new line;
        new1->head=NULL;
        new1->tail=NULL;
        new1->next=NULL;
        new1->prev=NULL;
        if(*head==NULL){
            *head=*tail=new1;
        }
        else{
            new1->prev=*tail;
            (*tail)->next=new1;
            *tail=new1;
        }
        std::string line;
        getline(file, line);
        char ch;
        for(int i=0;i<line.size();i++){
            if(line[i]!='\r'){
                insert_last(line[i],&new1->head,&new1->tail);
            }
            //std::cout<<line[i]<<' ';
        }
        insert_last('\n',&new1->head,&new1->tail);
        *lines+=1;
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