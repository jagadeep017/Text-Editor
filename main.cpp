/* Name  : Ganta Jagadeep
    Aim  : To write a program that acts like a command line text editer.
    Date : 02/01/2025
*/

#include <ncurses.h>
#include "main.h"
#include <signal.h>


void handler(int signum){
    endwin();
    exit(0);
}

int main(int argc, char *argv[]) {      //argv is the file name
    int ch;        //char to store user input

    text t(argv[1]);        //create a text object with the file name

    initscr();
    int y, x;           //rows and col values of terminal
    getmaxyx(stdscr, y, x); //get terminal row and col values
    // raw();

    t.display(y, x);       //display
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    init_pair(COLOR_UI, COLOR_MAGENTA, 0);
    init_pair(COLOR_ERROR, COLOR_WHITE, COLOR_RED);
    init_pair(COLOR_KEYWORDS, COLOR_BLUE, 0);
    init_pair(COLOR_TYPES, COLOR_RED, 0);
    init_pair(COLOR_COMMENTS, COLOR_GREEN, 0);
    init_pair(COLOR_VISUAL, COLOR_BLACK, COLOR_BLUE);
    //set the delay for escape sequence
    set_escdelay(50);
    signal(SIGINT, handler);
    // signal(SIGINT, SIG_IGN);    // Disable Ctrl-C shortcut signal

    while((ch = getch())){      //get the user input
        t.error.clear();
        getmaxyx(stdscr, y, x);     //get terminal row and col values

        if(t.mode != COMMAND && ch == KEY_DC){       //if the user input is delete
            t.delete_after(LOG);        //delete the character after the cursor
        }
        else if(ch == '\033'){         //if the user input is escape
            t.r_command.clear();      //clear the command
            t.mode = READ;             //change the mode to read
        }
        else if(t.esc_seq(ch));
        else if(t.mode == INSERT){
            if (ch == KEY_BACKSPACE) {     //if the user input is backspace
                t.delete_before(LOG);       //delete the character before the cursor
            }
            else if (ch == '\n') {                //if the user input is enter
                t.insert_before('\n', LOG);
            }
            else if(ch == '\t'){                  //if the user input is tab
                for(int i = 0; i < 4; i++){
                    t.insert_before(' ', LOG);
                }
            }
            else{                               //if the user input is a character
                t.insert_before(ch, LOG);
            }
        }
        else if(t.mode == REPLACE){
            if(ch < 255 && is_valid(ch)){
                t.replace_cur(ch);
            }
        }
        else if(t.mode == COMMAND){
            if(ch == '\n'){
                //do the command
                t.command_do();
                t.mode = READ;
            }
            else if(ch == '\033'){
                t.mode = READ;
            }
            else{
                t.insert_cmd(ch);
            }
        }
        else{
            t.r_command.push_back(ch);
            t.r_command_do();
        }
        t.display(y, x);
    }
    return 0;
}
