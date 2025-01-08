#ifndef DISPLAY_H
#define DISPLAY_H

#include "main.h"
void display(int row,int col,text& t);

void add_data(char* name,struct charn **head,struct charn **tail);

void insert_last(char data,struct charn **head,struct charn **tail);

#endif