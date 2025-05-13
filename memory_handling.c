#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct Line** create_line_ptrs_array(void) {
    // struct Line* first_line = malloc(sizeof(struct Line));
    // char* symbols = malloc(sizeof(char) * INITIAL_LINE_CAPACITY);
    //
    // first_line->first_symbol = symbols;
    // first_line->capacity = INITIAL_LINE_CAPACITY;
    // first_line->filled = 0;

    struct Line** lines = malloc(sizeof(*lines));
    add_a_new_line(lines, 0);
    // lines[0] = first_line;
    return lines;
}


void alloc_more_symbols_in_line(struct Line* line_ptr) {
    char *symbols = realloc(line_ptr->first_symbol, sizeof(char) * line_ptr->capacity * 2);

    if (symbols != NULL) {
        line_ptr->first_symbol = symbols;
        line_ptr->capacity *= 2;
    }
    else {
        fprintf(stderr, "Memory allocation for symbols failed in realloc\n");
        exit(1);
    }
}

struct Line** alloc_more_ptrs_in_array(struct Line** lines, int line_ptrs_array_capacity) {
    struct Line** new_lines = realloc(lines, sizeof(*lines) * line_ptrs_array_capacity * 2);

    if (new_lines != NULL) {
        return new_lines;
    }
    fprintf(stderr, "Memory allocation for symbols failed in realloc\n");
    exit(1);
}
