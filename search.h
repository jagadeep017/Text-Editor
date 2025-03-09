#include "main.h"
#include <string>
#ifndef SEARCH_H
#define SEARCH_H

void set_line_color(struct line* Cursorline);

bool is_keyword(const std::string& str);

bool is_datatype(const std::string& str);

void set_word_color(std::string& buffer, struct charn *start, struct charn *end);

#endif