#include "main.h"
#include "display.h"
#include <cstring>
#include <iostream>
#include <fstream>

void display(int row,int col,text t){
    system("clear");    //clear the screen

}

void add_data(char* name,struct charn **head,struct charn **tail){
    char *temp=strstr(name,".");
    if(temp==NULL){
        std::cout<<"Invalid file name\n";
        exit(0);
    }
    if(strcmp(temp,".txt")!=0||strcmp(temp,".c")!=0||strcmp(temp,".cpp")!=0){
        std::cout<<"Invalid file type\n";
        exit(0);
    }
    std::ifstream file(name);
    if(!file.is_open()){
        std::cout<<"File "<<name<<" not found\n";
        exit(0);
    }
    while(!file.eof()){
        insert_last(file.get(),head,tail);
    }
    file.close();
}

void insert_last(char c,struct charn **head,struct charn **tail){
    struct charn *new1=new charn;
    if(new1==NULL){
        printf("Memory allocation failed\n");
        exit(0);
    }
    new1->data=c;
    new1->next=NULL;
    if(head==NULL){
        *head=new1;
        *tail=new1;
    }
    else{
        (*tail)->next=new1;
        *tail=new1;
    }
}