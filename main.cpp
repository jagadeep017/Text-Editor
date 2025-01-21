/* Name: Ganta Jagadeep
    Aim : To write a program that acts like a command line text editer.
    Date: 02/01/2025
*/

#include <curses.h>
#include "main.h"
#include "edit.h"
#include "display.h"
#include <signal.h>


int main(int argc, char *argv[]) {      //argv is the fine name
    char ch,flag=0;        //char to store user input

    text t(argv[1]);        //create a text object with the file name

    initscr();
    int y, x;           //rows and col values of terminal
    getmaxyx(stdscr, y, x); //get terminal row and col values
    raw();
    display(y,x,t);       //display
    noecho();
    cbreak();
    
    signal(SIGINT, SIG_IGN);    // Disable Ctrl-C shortcut

    while((ch=getch())){      //get the user input
        if(ch==-102){           //if the '~Z' means change in terminal size
            getmaxyx(stdscr, y, x);     //get terminal row and col values
            display(y,x,t);     //display
        }
        else if(ch=='\033'){         //if the user input is escape      
            ch=getch();       //get the next character
            if(ch=='['){        //if the next character is [
                ch=getch();   //get the next character
                if(ch=='A'){    //if the next character is A
                    move_cursor(-1,t);      //move the cursor up
                }
                else if(ch=='B'){   //if the next character is B
                    move_cursor(1,t);      //move the cursor down
                }
                else if(ch=='C'){   //if the next character is C
                    move_cursor_side(1,t);      //move the cursor right
                }
                else if(ch=='D'){   //if the next character is D
                    move_cursor_side(-1,t);      //move the cursor left
                }
            }
        }
        else if (ch=='\n') {                //if the user input is enter
            insert_before('\n', t);
        }
        else if(ch=='\t'){                  //if the user input is tab
            for(int i=0;i<4;i++){
                insert_before(' ',t);
            }
        }
        else{                               //if the user input is a character
            insert_before(ch, t);
        }
        display(y,x,t);
        if(ch=='q'){
            endwin();   //end the session and resorte the terminal
            return 0;
        }
    }
    return 0;
}