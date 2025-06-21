//
// Created by Yulia Mala on 28.05.2025.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "UserCommands.h"
#include "TextEditor.h"

void print_help() {
    for (const auto& cmd : commands) {
        std::cout << cmd.id << " - " << cmd.description << "\n";
    }
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
    }
    while ((ch = getchar()) != '\n' && ch != EOF);
    return text_length;
}

void end_program(TextEditor *editor) {
    delete editor;
    exit(0);
}