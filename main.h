#ifndef MAIN_H
#define MAIN_H

#include <iostream>

typedef enum Mode {
    READ,
    INSERT,
    AUTOSUGGESTION,
    COMMAND,
    EXIT
}mode;

typedef enum Undotree{
    DELETE,
    ADD,                //insert
    UNDO,
    REDO,
}undotree;

struct charn{
    char data;
    unsigned short color;
    struct charn* next;
    struct charn* prev;
    charn(){
        data='\0';
        color=0;
        next=NULL;
        prev=NULL;
    }
};

struct line{
    struct charn* head;
    struct charn* tail;
    struct line* next;
    struct line* prev;
    unsigned int len;
    public:
    line(){
        head=NULL;
        tail=NULL;
        next=NULL;
        prev=NULL;
    }
};

struct str{
    std::string data;
    struct str* next;
    struct str* prev;
    struct line* Line;
    unsigned int col;
    unsigned char type;
    str(){
        data="\0";
        next=NULL;
        prev=NULL;
        Line=NULL;
        type='\0';
        col=0;
    }
};

struct undo{
    struct str* head;
    struct str* tail;
    undo(){
        head=NULL;
        tail=NULL;
    }
};

// struct redo{
//     struct str* head;
//     struct str* curr;
//     redo(){
//         head=NULL;
//         curr=NULL;
//     }
// };


class text{  
    struct line* head;
    struct line* tail;
    struct line* Cursorline;
    struct charn* Cursor;               //to store the address of the cursor
    unsigned int cursor_line;
    unsigned int prev_cursor_col;
    unsigned int cursor_col;
    unsigned int line_count;
    unsigned int line_offset;
    struct undo Undo;
    struct undo Redo;
    std::string command;
    public:
    unsigned int mode;
    text(char* filename){
        head = NULL;
        tail = NULL;
        cursor_line  = 0;
        prev_cursor_col=0;
        cursor_col=0;
        line_count=0;
        line_offset=0;
        mode=0;
        add_data(filename,&head,&tail,&line_count);
        Cursorline=head;
        Cursor=Cursorline->head;
        command=":";
    }

    //display.cpp
    void display(unsigned short int row,unsigned short int col);
    
    //file.cpp
    void add_data(char* filename,struct line **head,struct line **tail,unsigned int *lines);
    void insert_last(char data,struct charn **head,struct charn **tail);
    void save();
    
    //insert.cpp
    void insert_before(char data);
    void delete_before();
    void delete_after();
    void insert_cmd(char ch);
    void pop_ch_cmd();

    //edit.cpp
    void move_cursor(int pos);
    void move_cursor_side(int pos);
    unsigned int len(struct line * head);

    //command.cpp
    void command_do();

    //undo.cpp
    void undo();
    void redo();
    void insert_undo(char ch);
};

#endif
