#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void print_help(void) {
    printf("Commands:\n"
           "1 - Append text symbols to the end\n"
           "2 - Start the new line\n"
           "3 - Save to file\n"
           "4 - Load from file\n"
           "5 - Print current text to console\n"
           "6 - Insert text by line and symbol index\n"
           "7 - Search text\n"
           "8 - END PROGRAM\n");
}

void append_to_the_end(struct Line** lines, int num_of_lines) {
    struct Line* last_line = lines[num_of_lines - 1];

    char buff[1000];
    printf("Type a text to append: ");
    fgets(buff, sizeof(buff), stdin);
    size_t append_length = strlen(buff) - 1;

    if (buff[append_length] == '\n') {
        buff[append_length] = '\0';
    }

    while (append_length > last_line->capacity - last_line->filled) {
        alloc_more_symbols_in_line(last_line);
    }
    memcpy(last_line->first_symbol + last_line->filled, buff, append_length);
    last_line->filled += append_length;
}


void add_a_new_line(struct Line** lines, int num_of_lines) {
    struct Line* new_line = malloc(sizeof(struct Line));
    char* symbols = malloc(sizeof(char) * INITIAL_LINE_CAPACITY);

    new_line->first_symbol = symbols;
    new_line->capacity = INITIAL_LINE_CAPACITY;
    new_line->filled = 0;

    lines[num_of_lines] = new_line;
}

void print_current_text(struct Line** lines, int num_of_lines) {
    for (int i = 0; i < num_of_lines; i++) {
        printf("%s \n", lines[i]->first_symbol);
    }
}

void insert_text_on_index(int line_index, int symbol_index, struct Line** lines, char* source, int append_length) {
    struct Line* line_to_insert = lines[line_index];

    while (append_length > line_to_insert->capacity - line_to_insert->filled) {
        alloc_more_symbols_in_line(line_to_insert);
    }

    int num_of_symbols_after_insertion_place = line_to_insert->filled - symbol_index;
    char symbols_after_insert [num_of_symbols_after_insertion_place];
    memcpy(
        symbols_after_insert,
        line_to_insert->first_symbol + symbol_index,
        num_of_symbols_after_insertion_place);

    memcpy(line_to_insert->first_symbol + symbol_index, source, append_length);

    memcpy(
        line_to_insert->first_symbol + symbol_index + append_length,
        symbols_after_insert,
        num_of_symbols_after_insertion_place);

    line_to_insert->filled += append_length;
}


void search_substring(
    char* str_to_search,
    struct Line** lines,
    int length_to_search,
    int num_of_lines
    ) {
    for (int i = 0; i < num_of_lines; i++) {
        for (int j = 0; j <= lines[i]->filled - length_to_search; j++) {
            if (memcmp(str_to_search, lines[i]->first_symbol + j, length_to_search) == 0) {
                printf("line %d, symbol %d (0-based indexes)\n", i, j);
            }
        }
    }
}

void save_to_file(char* filename, struct Line** lines, int num_of_lines) {
    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        for (int i = 0; i < num_of_lines; i++) {
            fwrite(lines[i]->first_symbol, sizeof(char), lines[i]->filled, file);
            fputc('\n', file);
        }

        fclose(file);
        return;
    }
    printf("Can't open such a file... Try another filename \n");
}

void load_from_file(char* filename, struct Line** lines, int num_of_lines) {
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        char buff [1000];
        int lines_added = 0;
        while (fgets(buff, sizeof(buff), file)) {

            size_t line_length = strlen(buff) - 1;
            if (buff[line_length] == '\n') {
                buff[line_length] = '\0';
            }
            add_a_new_line(lines, num_of_lines + lines_added);
            lines_added++;
        }

        fclose(file);
        return;
    }
    printf("Can't open such a file... Check filename \n");
}
