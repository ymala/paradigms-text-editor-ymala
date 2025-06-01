//
// Created by Yulia Mala on 28.05.2025.
//

#ifndef UTILS_H
#define UTILS_H

void print_help();

char* get_text_from_user(int* out_length = nullptr);

void get_index_from_user(int &line_index, int &symbol_index);

int get_length_from_user();

struct Cursor {
    int line_index = 0;
    int symbol_index = 0;
};

#endif //UTILS_H
