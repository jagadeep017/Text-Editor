#ifndef EDIT_H
#define EDIT_H

#include "main.h"

void move_cursor(int pos,text& t);

void move_cursor_side(int pos,text& t,int max);

unsigned int len(struct line * head);

#endif