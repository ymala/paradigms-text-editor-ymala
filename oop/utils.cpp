//
// Created by Yulia Mala on 28.05.2025.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "TextEditor.h"

void print_help() {
    printf("Commands:\n"
           "1 - Insert on cursor\n"
           "2 - Start new line\n"
           "3 - Save to file        4 - Load from file\n" //зараз вставляє в кінець файлу, а не на курсор
           "5 - Print to console\n"
           "6 - Move cursor \n"
           "7 - Insert with replacement \n"
           "8 - Search text\n"
           "9 - Delete text \n"
           "10 - Cut \n"
           "11 - Copy \n"
           "12 - Paste \n"
           "13 - Undo               14 - Redo \n"
           "15 - END PROGRAM\n");
}

char* get_text_from_user(int* out_length) {
    char buff[1000];
    printf("Type a text: ");
    fgets(buff, sizeof(buff), stdin);

    size_t line_length = strlen(buff);
    if (line_length > 0 && buff[line_length - 1] == '\n') {
        buff[line_length - 1] = '\0';
        line_length--;
    }
    char* result = (char*)malloc(line_length + 1);

    memcpy(result, buff, line_length);
    result[line_length] = '\0';
    if (out_length != nullptr) {
        *out_length = (int)line_length;
    }

    return result;
}

void get_index_from_user(int &line_index, int &symbol_index) {
    int ch;
    printf("Enter line and index starts from 0 (for ex. 0 6): ");
    if (scanf("%d %d", &line_index, &symbol_index) != 2) {
        printf("Invalid input. Two integers expected\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

int get_length_from_user() {
    int ch;
    int text_length = 0;
    printf("Enter length: ");
    if (scanf("%d", &text_length) != 1) {
        printf("Invalid input. One integer expected\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    return text_length;
}

void end_program(TextEditor *editor) {
    delete editor;
    exit(0);
}