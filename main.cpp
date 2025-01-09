/* Name: Ganta Jagadeep
    Aim : To write a program that acts like a command line text editer.
    Date: 02/01/2025
*/

#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "main.h"
#include "edit.h"
#include "display.h"

using namespace std;

int main(int argc, char *argv[]) {      //argv is the fine name
    char ch;        //char to store user input
    struct winsize w;
    text t(argv[1]);        //create a text object with the file name
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {   //get the size of the terminal window w.ws_row and w.ws_col
        std::cout<<"Error in getting the terminal size\n";
        return 1;
    }
    display(w.ws_row,w.ws_col,t);       //display

    while((ch=getchar())){      //get the user input
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {   //get the size of the terminal window w.ws_row and w.ws_col
            std::cout<<"Error in getting the terminal size\n";
            return 1;
        }
        if(ch=='\033'){         //if the user inp            
        ch=getchar();       //get the next character
            if(ch=='['){        //if the next character is [
                ch=getchar();   //get the next character
                if(ch=='A'){    //if the next character is A
                    move_cursor(-1,t);      //move the cursor up
                }
                else if(ch=='B'){   //if the next character is B
                    move_cursor(1,t);      //move the cursor down
                }
                else if(ch=='C'){   //if the next character is C
                    move_cursor_side(1,t,w.ws_col);      //move the cursor right
                }
                else if(ch=='D'){   //if the next character is D
                    move_cursor_side(-1,t,w.ws_col);      //move the cursor left
                }
            }
        }
        display(w.ws_row,w.ws_col,t);


        }
    return 0;
}