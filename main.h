#ifndef MAIN_H
#define MAIN_H

typedef enum Mode {
    READ,
    INSERT,
    AUTOSUGGESTION,
    EXIT
}mode;

struct charn{
    char data;
    unsigned short color;
    struct charn* next;
    struct charn* prev;
};

struct line{
    struct charn* head;
    struct charn* tail;
    struct line* next;
    struct line* prev;
};

void add_data(char* filename,struct line **head,struct line **tail,unsigned int *lines);

class text{  
    struct line* head;
    struct line* tail;
    struct line* Cursorline;
    struct charn* Cursor;               //to store the address of the cursor
    unsigned int cursor_line;
    unsigned int prev_line_len;
    unsigned int prev_cursor_col;
    unsigned int cursor_col;
    unsigned int line_count;
    unsigned int line_offset;
    char atend;                         //to check if the cursor is at the end or at the beginning
    public:
    unsigned int mode;
    text(char* filename){
        head = 0;
        tail = 0;
        Cursorline=0;
        cursor_line  = 0;
        atend = 0;
        prev_line_len=0;
        prev_cursor_col=0;
        cursor_col=0;
        line_count=0;
        line_offset=0;
        mode=0;
        add_data(filename,&head,&tail,&line_count);
    }
    friend void display(unsigned short int row,unsigned short int col,text& t);
    friend void add_data(char* filename,struct charn **head,struct charn **tail,unsigned int *lines);
    friend void insert_last(char data,struct charn **head,struct charn **tail);
    friend void insert_before(char data,text& t);
    friend void delete_before(text& t);
    friend void delete_after(text& t);
    friend void move_cursor(int pos,text& t);
    friend void move_cursor_side(int pos,text& t);
};

#endif
