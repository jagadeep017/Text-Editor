/* Name: Ganta Jagadeep
    Aim : To write a program that acts like a command line text editer.
    Date: 02/01/2025
*/

#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "display.h"

using namespace std;

int main(int argc, char *argv[]) {      //argv is the fine name
    char ch;        //char to store user input
    struct winsize w;

    while(1){
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {   //get the size of the terminal window w.ws_row and w.ws_col
            perror("ioctl");
            return 1;
        }

        ch=getchar();       //get the user input

    }
    return 0;
}
