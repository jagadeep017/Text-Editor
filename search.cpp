#include "main.h"
#include "search.h"

const char *keywords[13]={"if","else","while","for","do","switch","case","default","break","continue","return","goto","sizeof"};
const char *datatypes[19]={"int","char","float","double","long","short","unsigned","signed","void","struct","enum","union","auto","register","static","extern","const","volatile","typedef"};

//sets color for the cursorline line
void set_line_color(struct line *Cursorline){
    char flag=1;
    struct charn *temp=Cursorline->head,*temp1;
    std::string buffer="";
    while(temp->data!='\n'){
        if((temp->data<='z'&&temp->data>='a')||(temp->data<='Z'&&temp->data>='A')||(temp->data<='9'&&temp->data>='0')||temp->data=='_'){
            buffer.push_back(temp->data);
            if(flag){
                temp1=temp;
                flag=0;
            }
        }
        else{
            flag=1;
            if(buffer.size()){
                if(is_keyword(buffer)){
                    while(temp!=temp1){
                        temp1->color=3;
                        temp1=temp1->next;
                    }
                }
                else if(is_datatype(buffer)){
                    while(temp!=temp1){
                        temp1->color=4;
                        temp1=temp1->next;
                    }
                }
                else{
                    while(temp!=temp1){
                        temp1->color=0;
                        temp1=temp1->next;
                    }
                }
                buffer.clear();
            }
            temp->color=0;
        }
        temp=temp->next;
    }
}

bool is_keyword(const std::string &str){
    for(int i=0;i<13;i++){
        if(str.compare(keywords[i])==0){
            return true;
        }
    }
    return false;
}

bool is_datatype(const std::string &str){
    for(int i=0;i<19;i++){
        if(str.compare(datatypes[i])==0){
            return true;
        }
    }
    return false;
}