#include "main.h"
#include <curses.h>

void text::command_do(){
    //wq save and quit
    if(!command.compare(":wq")){
        endwin();   //end the session and resorte the terminal
        save();
        exit(0);
    }
    //q quit
    else if(!command.compare(":q")){
        //check if any changes where made
        endwin();   //end the session and resorte the terminal
        exit(0);
    }
    //q! quit without saving
    else if(!command.compare(":q!")){
        endwin();   //end the session and resorte the terminal
        exit(0);
    }
    //w write a new file name
    //dd to delete the line in read mode
    //:[start],[end]d delete lines from start to end
    //dl or x to delete letter in read mode
    //dw delete word in read mode
    //yy to copy line in read mode
    //p to paste in readf mode
    //% go to the matching bracket in read mode
    //u to undo
    //ctrl-r redo
    // /word to search word and go to the next occurance
    // :number jump to the number
    command.clear();
    command.push_back(':');
    
}