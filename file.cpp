#include "main.h"
#include <cstring>
#include <iostream>
#include <fstream>

//addeds the file content to the linked list
void text::add_data(char* name,struct line **head,struct line **tail,unsigned int *lines){
    if(!name){
        std::cout<<"no file name found"<<std::endl;
        exit(0);
    }
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
    struct line* temp1=*head;
    if(!file.is_open()){
        struct line* new1=new line;
        insert_last('\n',&new1->head,&new1->tail);
        *head=*tail=new1;
        return;
    }
    while(!file.eof()){
        struct line* new1=new line;
        if(*head==NULL){
            *head=*tail=new1;
        }
        else{
            new1->prev=*tail;
            (*tail)->next=new1;
            *tail=new1;
        }
        std::string line;
        getline(file, line);    //one line at a time
        char ch;
        for(int i=0;i<line.size();i++){
            if(line[i]!='\r'){
                insert_last(line[i],&new1->head,&new1->tail);
            }
        }
        insert_last('\n',&new1->head,&new1->tail);
        *lines+=1;
    }
    file.close();
}

//inserts the character at the end of the linked list
void text::insert_last(char c,struct charn **head,struct charn **tail){
    struct charn *new1=new charn;
    if(new1==NULL){
        std::cout<<"Memory allocation failed"<<std::endl;
        exit(0);
    }
    new1->data=c;
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

//saves the file(semi implemented)
void text::save(){
    std::ofstream file;
    file.open("temp.txt");
    if(!file.is_open()){
        std::cout<<"Unable to save file"<<std::endl;
        exit(0);
    }
    struct line *temp=head;
    struct charn *temp1;
    while(temp){
        temp1=temp->head;
        while(temp1){
            if(temp1->data=='\n'){
                file.put('\r');
            }
            file.put(temp1->data);
            temp1=temp1->next;
        }
        temp=temp->next;
    }
}