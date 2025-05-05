#include "main.h"
#include "highlight.h"

const char *keywords[13] = {"if", "else", "while", "for", "do", "switch", "case", "default", "break", "continue", "return", "goto", "sizeof"};
const char *datatypes[19]={"int", "char", "float", "double", "long", "short", "unsigned", "signed", "void", "struct", "enum", "union", "auto", "register", "static", "extern", "const", "volatile", "typedef"};

//sets color for the cursorline line
void set_line_color(struct line *Cursorline){
    static char multi_comment = 0;
    char flag = 1, comm_flag = 0;
    struct charn *temp = Cursorline->head, *temp1, *comm = NULL;
    std::string buffer = "";
    while(temp->data != '\n'){
        if(comm_flag || multi_comment){
            break;
        }
        else if(temp->data == '/' && temp->prev && temp->prev->data == '/'){
            comm_flag = 1;
            comm=temp->prev;
        }
        if((temp->data <= 'z' && temp->data >= 'a') || (temp->data <= 'Z' && temp->data >= 'A') || (temp->data <= '9' && temp->data >= '0') || temp->data == '_'){
            buffer.push_back(temp->data);
            if(flag){
                temp1 = temp;
                flag = 0;
            }
        }
        else{
            flag=1;
            set_word_color(buffer, temp1, temp);
            temp->color = COLOR_NILL;
        }
        temp = temp->next;
    }
    if(comm_flag || multi_comment){
        while(comm->data != '\n'){
            comm->color = COLOR_COMMENTS;
            comm = comm->next;
        }
    }
    else if(buffer.size()){
        set_word_color(buffer, temp1, temp);
    }
}

bool is_keyword(const std::string &str){
    for(int i = 0; i < 13; i++){
        if(str.compare(keywords[i]) == 0){
            return true;
        }
    }
    return false;
}

bool is_datatype(const std::string &str){
    for(int i = 0; i < 19; i++){
        if(!str.compare(datatypes[i])){
            return true;
        }
    }
    return false;
}

void set_word_color(std::string& buffer,struct charn *start,struct charn *end){
    if(buffer.size()){
        if(is_keyword(buffer)){
            while(start != end){
                start->color = COLOR_KEYWORDS;
                start = start->next;
            }
        }
        else if(is_datatype(buffer)){
            while(start != end){
                start->color = COLOR_TYPES;
                start = start->next;
            }
        }
        else{
            while(start != end){
                start->color = COLOR_NILL;
                start = start->next;
            }
        }
        buffer.clear();
    }
}
