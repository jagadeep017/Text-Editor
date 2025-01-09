#ifndef MAIN_H
#define MAIN_H

typedef enum Mode{
    INSERT,
    READ,
}mode;

struct charn{
    char data;
    struct charn* next;
    struct charn* prev;
};

void add_data(char* filename,struct charn **head,struct charn **tail);

class text{  
    struct charn* head;
    struct charn* tail;
    unsigned int cursor;
    unsigned int offset;
    unsigned int offset2;
    unsigned int prev_cursor;
    char atend;
    public:
    text(char* filename){
        head = 0;
        tail = 0;
        cursor  = 0;
        offset = 0;
        offset2 = 0;
        atend = 0;
        prev_cursor = 0;

        add_data(filename,&head,&tail);
    }
    friend void display(int row,int col,text& t);
    friend void add_data(char* filename,struct charn **head,struct charn **tail);
    friend void insert_last(char data,struct charn **head,struct charn **tail);
    friend void move_cursor(int pos,text& t);
    friend void move_cursor_side(int pos,text& t,int max);
};

#endif
