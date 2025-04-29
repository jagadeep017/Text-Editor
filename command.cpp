#include "main.h"
#include "highlight.h"
#include <cstdint>
#include <ncurses.h>

char is_num(std::string str,unsigned int offset){
    for(int i = offset; i < str.size(); i++){
        if(str[i] > '9' || str[i] < '0'){
            return 0;
        }
    }
    return 1;
}


unsigned int str_to_num(std::string str,unsigned int offset){
    unsigned int res = 0;
    int i = offset;
    while(i < str.size() && (str[i] > '9' || str[i] < '0')){
        i++;
    }
    for(; i < str.size(); i++){
        res = res * 10 + str[i] - '0';
    }
    return res;
}

char is_valid(char ch){
    if((ch >= ' ' && ch <= '~')){     //if the character is a printable character
        return 1;
    }
    return 0;
}

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
    else if(!command.compare(":te")){   //temporary case used for testing
        // move_to(10,9);
    }
    //goto to that line number
    else if(is_num(command,1)){
        unsigned int temp = str_to_num(command,1);
        if (temp == 0) temp = 1;
        move_to(temp - 1, 0);
    }
    //search
    else if(command[1] == '/' || command[1] == '?'){
        search_mode = (command[1] == '/') ? FORWARD : BACKWARD;
        search.clear();
        search.append(command, 2);
        search_word();
    }
    //print error for unknown commands
    else{
        error.append("Not an editor command: ");
        error.append(command, 1);
    }
    //w write a new file name
    //:[start],[end]d delete lines from start to end
    //dw delete word in read mode
    //yy to copy line in read mode
    //p to paste in read mode
    //% go to the matching bracket in read mode
    //u to undo
    //ctrl-r redo
    // /word to search word and go to the next occurance
    // :number jump to the number
}

//command in read mode
void text::r_command_do(){
	//2w allows us to move the cursor 2 words forward.
//5j changes your cursor position to 5 lines below.
//3; lets you go to the next third occurrence of a character.
//Use b (back) to jump to the beginning of a word backwards
//Use e (end) to jump to the end of a word
//Use ge to jump to the end of a word backwards
//^: Moves to the first non-blank character of a line
// g_: Moves to the non-blank character at the end of a line
    //dd to delete the line in read mode
    if(r_command.back() == 'd' && r_command.size() == 2 && r_command[r_command.size() - 2] == 'd'){
        //delete the line
        int temp=1;
        r_command.pop_back(), r_command.pop_back();
        if(r_command.size() && is_num(r_command,0)){
            temp=str_to_num(r_command,0);
            if(temp == 0){          //if 0dd delete all content
                temp = line_count;
            }
        }
        for(int i=0;i<temp;i++){
            delete_line();
        }
        set_line_color(Cursorline);
        r_command.clear();
    }
    //search in normal mode
    else if(r_command[0] == '/' || r_command[0] == '?'){
        if(r_command.size() == 1){
            search.clear();
        }
        else if(r_command.back() == '\n'){
            search_mode = r_command[0] == '/' ? FORWARD :BACKWARD;
            search_word();
            r_command.clear();
        }
        else{
            search.push_back(r_command.back());
        }
    }
    //r + letter to replace the current letter
    else if(r_command.size() == 2 && r_command[r_command.size() - 2] == 'r'){
        if(is_valid(r_command.back())){
            replace_cur(r_command.back());
        }
        r_command.clear();
    }
    //dl or x to delete letter in read mode
    else if((r_command.back() == 'l' && r_command.size() == 2 && r_command[r_command.size() - 2] == 'd') || r_command.back() == 'X' || r_command.back() == 'x'){
        delete_after(LOG);
        r_command.clear();
    }
    //h or H move cursor left
    else if(r_command.back() == 'h' || r_command.back() == 'H'){
        move_cursor_side(-1);
        r_command.clear();
    }
    //l or L move cursor right
    else if(r_command.back() == 'l' || r_command.back() == 'L'){
        move_cursor_side(1);
        r_command.clear();
    }
    //j or J move cursor down
    else if(r_command.back() == 'j' || r_command.back() == 'J'){
        move_cursor(1);
        r_command.clear();
    }
    //k or K move cursor up
    else if(r_command.back() == 'k' || r_command.back() == 'K'){
        move_cursor(-1);
        r_command.clear();
    }
    //u for undo
    else if(r_command.back() == 'u'){
        undo(UNDO);
        set_line_color(Cursorline);
        r_command.clear();
    }
    //enter replace mode
    else if(r_command.back() == 'R'){
        mode = REPLACE;
        r_command.clear();
    }
    //ctrl-r for redo
    else if(r_command.back() == '\022'){
        undo(REDO);
        set_line_color(Cursorline);
        r_command.clear();
    }
    //move to the start of the line
    else if(r_command.back() == '0'){
        move_to(cursor_line, 0);
        r_command.clear();
    }
    //move to the end of the line
    else if(r_command.back() == '$'){
        move_to(cursor_line, UINT32_MAX);
        r_command.clear();
    }
    //move to start
    else if(r_command.back() == 'g' && r_command.size() == 2 && r_command[r_command.size() - 2] == 'g'){
        move_to(0, 0);
        r_command.clear();
    }
    //enter into insert mode
    else if(r_command.back() == 'i' || r_command.back() == 'I' || r_command.back() == 'a' || r_command.back() == 'A'){
        switch(r_command.back()){
            case 'I':                   //move to the first non blank character
                move_to(cursor_line, 0);
                while(Cursor->data == ' ' && Cursor->data != '\n'){
                    move_cursor_side(1);
                }
                break;
            case 'a':
                if(Cursor->data != '\n'){
                    move_cursor_side(1);
                }
                break;
            case 'A':
                move_to(cursor_line, UINT32_MAX);
                break;
        }
        mode = INSERT;
        r_command.clear();
    }
    //enter command mode
    else if(r_command.back() == ':'){
        mode = COMMAND;
        command.clear();
        command.push_back(':');
        r_command.clear();
    }
    //goto a row
    else if(r_command.back() == 'G'){
        r_command.pop_back();
        if(!r_command.size()){
            move_to(line_count-1, 0);
        }
        else{
            unsigned int temp = str_to_num(r_command,0);
            if (temp == 0) temp = 1;
            move_to(temp - 1, 0);
        }
        r_command.clear();
    }
    //search with 'n' and ''N'
    else if(r_command.size() == 1 && ( r_command.back() == 'n' || r_command.back() == 'N' )){
        search_mode = r_command.back() == 'n'? FORWARD : BACKWARD;
        search_word();
        r_command.clear();
    }
    //enter visual mode
    else if(r_command.back() == 'v'){
        if(mode == VISUAL){
            mode = READ;
        }
        else{
            mode = VISUAL;
            visual_start.start_char = Cursor;
        }
        visual_line = cursor_line;
        r_command.clear();
    }
    else if (r_command.back() == 'V'){
        if(mode == VISUAL_LINE){
            mode = READ;
        }
        else{
            mode = VISUAL_LINE;
            visual_start.start_line = Cursorline;
        }
        visual_line = cursor_line;
        r_command.clear();
    }
}

//to perform esc sequence
char text::esc_seq(int ch){
    if(ch == KEY_LEFT){
        if(mode == COMMAND){

        }
        else{
            move_cursor_side(-1);
        }
        return 1;
    }
    else if(ch == KEY_RIGHT){
        if(mode == COMMAND){

        }
        else{
            move_cursor_side(1);
        }
        return 1;
    }
    else if(ch == KEY_UP){
        if(mode == COMMAND){

        }
        else{
            move_cursor(-1);
        }
        return 1;
    }
    else if(ch == KEY_DOWN){
        if(mode == COMMAND){

        }
        else{
            move_cursor(1);
        }
        return 1;
    }
    else if(ch == KEY_BACKSPACE){
        if(mode == COMMAND){
            pop_ch_cmd();
        }
        else if(mode == INSERT){
            delete_before(LOG);
        }
        return 1;
    }
    else if(ch == KEY_IC && mode != COMMAND){
        mode = !mode;
        return 1;
    }
    else if(ch > 255){
        return 1;
    }
    return 0;
}
