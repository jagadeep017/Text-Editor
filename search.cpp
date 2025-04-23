#include "main.h"
#include <cstddef>

void text::search_word(){
    struct charn *temp = NULL;
    struct line *temp1 = NULL;
    unsigned int char_c = 0, line_c = cursor_line;    //remembering at what line result is found
    if(search_mode == FORWARD){
        if(Cursorline->next){
            temp1 = Cursorline->next;
            line_c++;
        }
        else{
            temp1 = head;
            line_c = 0;
        }
    }
    else{
        if(Cursorline->prev){
            temp1 = Cursorline->prev;
            line_c--;
        }
        else{
            temp1 = tail;
            line_c = line_count - 1;
        }
    }
    while(temp1 != Cursorline){
        temp = temp1->head;
        char_c = 0;
        while(temp){
            if(temp->data == search[0]){
                struct charn *temp2 = temp;
                char found = 1;
                temp = temp->next;
                for(int i = 1; i < search.size() && temp; i++){
                    if(temp->data != search[i]){
                        temp = temp2;
                        found = 0;
                        break ;
                    }
                    temp = temp->next;
                }
                if(found){
                    move_to(line_c, char_c);
                    return ;
                }
                else{
                    temp = temp2->next;
                }
            }
            temp = temp->next;
            char_c++;
        }
        if(search_mode == FORWARD){
            if(temp1->next){
                temp1 = temp1->next;
                line_c++;
            }
            else{
                temp1 = head;
                line_c = 0;
            }
        }
        else{
            if(temp1->prev){
                temp1 = temp1->prev;
                line_c--;
            }
            else{
                temp1 = tail;
                line_c = line_count - 1;
            }
        }
    }
    error.append("Err: Pattern not found: ");
    error.append(search);
}