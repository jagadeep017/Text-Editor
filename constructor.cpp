#include "main.h"

//constructor to initialize the text object
text::text(char* filename){
    head = NULL;
    tail = NULL;
    cursor_line = 0;
    prev_cursor_col = 0;
    cursor_col = 0;
    line_count = 0;
    mode = 0;
    visual_line = 0;
    add_data(filename, &head, &tail, &line_count);
    Cursorline = head;
    Cursor = Cursorline->head;
    command = "";
    error = "";
    r_command = "";
    search = "";
    yank = "";
    search_mode = FORWARD;
    visual_start.start_line = NULL;
}

//destructor to delete the text object
text::~text(){
    struct line *temp;
    struct charn *temp1;
    while((temp = head)){
        while((temp1 = temp->head)){
            temp->head = temp1->next;
            delete temp1;
        }
        head = temp->next;
        delete temp;
    }
}