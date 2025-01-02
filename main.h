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
    text(char* filename);{
        head = NULL;
        tail = NULL;
        add_data(filename,&head,&tail);
    }
    friend void display(int row,int col,text t);
}

#endif