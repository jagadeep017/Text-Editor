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

class text{  
    struct charn* head;
    struct charn* tail;
    public:
    text(char* filename){
        head = 0;
        tail = 0;
        add_data(filename,&head,&tail);
    }
    void display(int row,int col,text t);
    void add_data(char* filename,struct charn **head,struct charn **tail);
    void insert_last(char data,struct charn **head,struct charn **tail);
};

#endif