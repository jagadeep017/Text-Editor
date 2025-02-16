/* Name: Ganta Jagadeep
    Aim : To write a program that acts like a command line text editer.
    Date: 02/01/2025
*/

#include <curses.h>
#include "main.h"
#include <signal.h>


int main(int argc, char *argv[]) {      //argv is the file name
    char ch;        //char to store user input

    text t(argv[1]);        //create a text object with the file name

    initscr();
    int y, x;           //rows and col values of terminal
    getmaxyx(stdscr, y, x); //get terminal row and col values
    raw();
    t.display(y,x);       //display
    noecho();
    // cbreak();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    // curs_set(0);                    //make the cursor invisible
    
    signal(SIGINT, SIG_IGN);    // Disable Ctrl-C shortcut

    while((ch=getch())){      //get the user input
        if(ch==-102){           //if the '~Z' means change in terminal size
            getmaxyx(stdscr, y, x);     //get terminal row and col values
        }
        else if(t.mode==READ&&ch==':'){
            t.mode=COMMAND;
        }
        else if(t.mode==READ&&ch=='i'){
            t.mode=INSERT;
        }
        else if(t.mode!=COMMAND&&ch=='~'){       //if the user input is ~
            t.delete_after();        //delete the character after the cursor
        }
        else if(ch=='\033'){         //if the user input is escape
            ch=getch();       //get the next character
            if(ch=='['){        //if the next character is [
                ch=getch();   //get the next character
                if(ch=='A'&&t.mode!=COMMAND){    //if the next character is A
                    t.move_cursor(-1);      //move the cursor up
                }
                else if(ch=='B'&&t.mode!=COMMAND){   //if the next character is B
                    t.move_cursor(1);      //move the cursor down
                }
                else if(ch=='C'&&t.mode!=COMMAND){   //if the next character is C
                    t.move_cursor_side(1);      //move the cursor right
                }
                else if(ch=='D'&&t.mode!=COMMAND){   //if the next character is D
                    t.move_cursor_side(-1);      //move the cursor left
                }
                else if(ch=='2'){
                    if(t.mode!=COMMAND){
                        t.mode=!t.mode;
                    }
                    ch=getch();
                }
            }
            else{
                t.mode=READ;
            }
        }
        else if(t.mode==INSERT){
            if (ch==127) {     //if the user input is backspace
                t.delete_before();       //delete the character before the cursor
            }
            else if (ch=='\n') {                //if the user input is enter
                t.insert_before('\n');
            }
            else if(ch=='\t'){                  //if the user input is tab
                for(int i=0;i<4;i++){
                    t.insert_before(' ');
                }
            }
            else{                               //if the user input is a character
                t.insert_before(ch);
            }
        }
        else if(t.mode==COMMAND){
            if(ch=='\n'){
                //do the command
                t.command_do();
                t.mode=READ;
            }
            else if(ch==127){
                t.pop_ch_cmd();
            }
            else{
                t.insert_cmd(ch);
            }
        }
        
        t.display(y,x);
    }
    return 0;
}