#include "main.h"
#include <curses.h>

//display the text in buffer on to the screen using ncurses
void text::display(unsigned short int row,unsigned short int col){
    // clear();                                                        //clear the screen
    curs_set(0);                                                    //make the cursor invisible
    move(0, 0);
    struct line *temp = head;
    unsigned int linecount = 0, charcount = 0, coursercol = 0, courselline = 0;
    unsigned short temp1 = 0, color = 0;
    unsigned int offset = 0, offset2 = 0;
    char visual = 0;
    
    if (cursor_line >= row - 4) {
        offset = cursor_line + 4 - row;
    }
    linecount = line_count ? line_count : 1;
    while(linecount){
        temp1++;
        linecount /= 10;
    }
    linecount = offset;
    while(linecount){
        temp = temp->next;
        linecount--;
    }
    linecount = offset;
    // while(1){
    //     struct line *ptr = temp;
    // }
    if((mode == VISUAL || mode == VISUAL_LINE) && visual_line < linecount){
        visual = 1;
    }
    while(temp && linecount - offset + offset2 < row - 1){
        charcount = 0;
        struct charn *temp2 = temp->head;
        attron(COLOR_PAIR(1));
        printw("%*d ",temp1,linecount + 1);
        attroff(COLOR_PAIR(1));
        if(visual){
            attron(COLOR_PAIR(6));
        }
        while(temp2 && linecount - offset + offset2 < row - 1){
            if(mode == VISUAL || mode == VISUAL_LINE){
                if(visual_start.start_char == temp2 || visual_start.start_line == temp){
                    visual = !visual;
                    if(visual){
                        attron(COLOR_PAIR(6));
                    }
                    else{
                        attroff(COLOR_PAIR(6));
                    }
                }
                if((mode == VISUAL && Cursor == temp2 ) || (mode == VISUAL_LINE && Cursorline == temp)){
                    visual = !visual;
                    if(visual){
                        attron(COLOR_PAIR(6));
                    }
                    else{
                        attroff(COLOR_PAIR(6));
                    }
                }
            }
            if(!visual){
                attron(COLOR_PAIR(temp2->color));
            }
            if(temp == Cursorline && temp2 == Cursor){
                if(temp2->data == '\n'){
                    printw(" %c", temp2->data);
                }
                else{
                    printw("%c", temp2->data);
                }
                courselline = linecount - offset + offset2;
                coursercol = charcount + temp1 + 1;
            }
            else{
                printw("%c", temp2->data);
            }
            if(!visual){
                attroff(COLOR_PAIR(temp2->color));
            }
            charcount++;
            temp2 = temp2->next;
            if(charcount + temp1 == col - 1 && temp2){
                charcount = 0;
                printw("%*s ", temp1, " ");
                offset2++;
            }
        }
        temp = temp->next;
        linecount++;
    }
    if(line_count<row-1){
        temp1 = row - 1 - line_count;
    }
    else if(cursor_line + 3 > line_count){
        temp1 = cursor_line + 3 - line_count;
    }
    else{
        temp1 = 0;
    }
    attron(COLOR_PAIR(1));
    while(temp1 > 0){
        printw("~\n");
        temp1--;
    }
    printw("%*c", col, ' ');
    if(error.empty() && mode != COMMAND ? 1 : col > 50){
        move(row - 1, col - 20);
        printw("Ln %d, Col %d, ", cursor_line + 1, cursor_col + 1);
        if(offset == 0){
            printw("TOP");
        }
        else if(line_count < row - 1 || cursor_line + 3 > line_count || temp1){
            printw("BOT");
        }
        else{
            printw("%d%%", (cursor_line * 100) / line_count);
        }
        linecount = cursor_line + 1;
    }
    move(row - 1, 0);
    if(mode == INSERT) {
        attron(A_BOLD);
        printw("-- INSERT --");
        attroff(A_BOLD);
    }
    else if(mode == VISUAL || mode == VISUAL_LINE){
        attron(A_BOLD);
        printw("-- VISUAL --");
        attroff(A_BOLD);
    }
    else if(mode == REPLACE){
        attron(A_BOLD);
        printw("-- REPLACE --");
        attroff(A_BOLD);
    }
    else if(error.size()){
        attron(COLOR_PAIR(2));
        printw("%s", error.c_str());
        attron(COLOR_PAIR(2));
    }
    else if(mode == COMMAND){
        attron(A_BOLD);
        printw("%s", command.c_str());
        attroff(A_BOLD);
    }
    if(mode != COMMAND){
        move(courselline,coursercol);
    }
    attroff(COLOR_PAIR(1));
    curs_set(1);                                                    //make the cursor visible
}
