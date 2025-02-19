#include "main.h"
#include <curses.h>

//run commands in command mode 
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
        if(Undo.head){                      //unsaved changes
            error.append("Error: No save since last change");
        }
        else{
            endwin();   //end the session and resorte the terminal
            exit(0);
        }
    }
    //q! quit without saving
    else if(!command.compare(":q!")){
        endwin();   //end the session and resorte the terminal
        exit(0);
    }
    else if(!command.compare(":undo")){
        undo();
    }
    else{
        error.append("Not an editor command: ");
        error.append(command,1);
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
}

//command in read mode
void text::r_command_do(){
    //dd to delete the line in read mode
    if(r_command.back()=='d'&&r_command[r_command.size()-2]=='d'){
        //delete the line
        delete_line();
        r_command.clear();
    }
    else if(r_command.back()=='h'){
        move_cursor_side(-1);
        r_command.clear();
    }
    else if(r_command.back()=='l'){
        move_cursor_side(1);
        r_command.clear();
    }
    else if(r_command.back()=='j'){
        move_cursor(1);
        r_command.clear();
    }
    else if(r_command.back()=='k'){
        move_cursor(-1);
        r_command.clear();
    }
    else if(r_command.back()=='u'){
        undo();
        r_command.clear();
    }
    else if(r_command.back()=='r'){
        redo();
        r_command.clear();
    }
    else if(r_command.back()=='i'||r_command.back()=='I'){
        mode=INSERT;
    }
    else if(r_command.back()==':'){
        mode=COMMAND;
        command.clear();
        command.push_back(':');
        r_command.clear();
    }
}