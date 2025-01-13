#ifndef MAIN_H
#define MAIN_H

typedef enum Action {
    INSERT,
    AUTOSUGGESTION,
    EXIT
}action;

struct charn{
    char data;
    struct charn* next;
    struct charn* prev;
};

void add_data(char* filename,struct charn **head,struct charn **tail);

class text{  
    struct charn* head;
    struct charn* tail;
    struct charn* prev;                //to store the address of the "\n" before the cursor 
    struct charn* Cursor;               //to store the address of the cursor
    unsigned int cursor;
    unsigned int prev_line_len;
    unsigned int prev_cursor_col;
    unsigned int cursor_col;
    char atend;                         //to check if the cursor is at the end or at the beginning
    public:
    text(char* filename){
        head = 0;
        tail = 0;
        prev = 0;
        cursor  = 0;
        atend = 0;
        prev_line_len=0;
        prev_cursor_col=0;
        cursor_col=0;
        add_data(filename,&head,&tail);
    }
    friend void display(unsigned short int row,unsigned short int col,text& t);
    friend void add_data(char* filename,struct charn **head,struct charn **tail);
    friend void insert_last(char data,struct charn **head,struct charn **tail);
    friend void move_cursor(int pos,text& t);
    friend void move_cursor_side(int pos,text& t);
};

#endif
