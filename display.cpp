#include "main.h"
#include "display.h"
#include <cstring.h>
#include <iostream>
#include <fstream>

void display(int row,int col,text t){
    system("clear");    //clear the screen

}

void add_data(char* name,struct charn **head,struct charn **tail){
    char *temp=strstr(name,".");
    if(temp==NULL){
        printf("Invalid file name\n");
        exit(0);
    }
    if(strcmp(temp,".txt")!=0||strcmp(temp,".c")!=0||strcmp(temp,".cpp")!=0){
        printf("Invalid file name\n");
        exit(0);
    }
    ifstream file(name);
    if(!file.is_open()){
        printf("Invalid file name\n");
        exit(0);
    }
    while(!file.eof()){
        insert_last(file.getchar());
    }

    
}

void insert_last(char c){
    struct charn *new=new charn;
    if(new==NULL){
        printf("Memory allocation failed\n");
        exit(0);
    }
    new->data=c;
    new->next=NULL;
    if(head==NULL){
        head=new;
        tail=new;
    }
    else{
        tail->next=new;
        tail=new;
    }
}