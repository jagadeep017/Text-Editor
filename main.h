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
    unsigned int Cursor ;
    unsigned int line;
    public:
    text(char* filename){
        head = 0;
        tail = 0;
        Cursor  = 0;
        line = 0;
        add_data(filename,&head,&tail);
    }
    friend void display(int row,int col,text& t);
    friend void add_data(char* filename,struct charn **head,struct charn **tail);
    friend void insert_last(char data,struct charn **head,struct charn **tail);
};

#endif