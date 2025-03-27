#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#define NOLOG   0
#define LOG     1

typedef enum Mode {
    READ,
    INSERT,
    REPLACE,
    AUTOSUGGESTION,
    COMMAND,
    EXIT
}mode;

typedef enum Undotree{
    DELETE,
    ADD,                //insert
    REPL,               //replace
    UNDO,
    REDO,
}undotree;

struct charn{
    char data;
    unsigned short color;
    struct charn* next;
    struct charn* prev;
    charn(){
        data = '\0';
        color = 0;
        next = NULL;
        prev = NULL;
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
        head = NULL;
        tail = NULL;
        next = NULL;
        prev = NULL;
    }
};

struct str{
    std::string data;
    struct str* next;
    struct str* prev;
    unsigned int line;
    unsigned int col;
    unsigned char type;
    str(){
        data = "\0";
        next = NULL;
        prev = NULL;
        line = 0;
        type = '\0';
        col = 0;
    }
};

struct undo{
    struct str* head;
    struct str* tail;
    undo() {
        head = NULL;
        tail = NULL;
    }
};


class text{  
    struct line* head;
    struct line* tail;
    struct line* Cursorline;            //to store the address of the cursor line
    struct charn* Cursor;               //to store the address of the cursor
    unsigned int cursor_line;
    unsigned int prev_cursor_col;
    unsigned int cursor_col;
    unsigned int line_count;
    struct undo Undo;
    struct undo Redo;
    public:
    std::string command;
    std::string r_command;
    std::string error;
    unsigned char mode;
    
    //constructor.cpp
    text(char* filename);
    ~text();

    //display.cpp
    void display(unsigned short int row, unsigned short int col);
    
    //file.cpp
    void add_data(char* filename, struct line **head, struct line **tail, unsigned int *lines);
    void insert_last(char data, struct charn **head, struct charn **tail);
    void save();
    
    //insert.cpp
    void insert_before(char data, unsigned char log);
    void delete_before(unsigned char log);
    void delete_after(unsigned char log);
    void delete_line();
    void insert_cmd(char ch);
    void pop_ch_cmd();
    void replace_cur(char ch);

    //edit.cpp
    void move_cursor(int pos);
    void move_cursor_side(int pos);
    unsigned int len(struct line * head);
    void move_to(unsigned int line, unsigned int col);

    //command.cpp
    void command_do();
    void r_command_do();
    char esc_seq(int ch);

    //undo.cpp
    void undo(char opr);
    void insert_undo(char ch, unsigned char type);
    void insert_line_undo();
    void push_to_redo(struct str* node);
    void push_to_undo(struct str* node);

};

/*command.cpp

check if the string is a number

returns 1 if the string is a number else 0
*/
char is_num(std::string str, unsigned int offset);

/*command.cpp

converts a string to a number

returns the number
*/
unsigned int str_to_num(std::string str, unsigned int offset);

/*command.cpp

check if the character is insertable or printable like an alphabet , number or a special character
*/
char is_valid(char ch);

#endif
