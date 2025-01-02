#include "main.h"
#include "display.h"
#include <cstring.h>
#include <iostream>
#include <fstream>

void display(int row,int col,text t){
    //clear the screen
    system("clear");

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

}

