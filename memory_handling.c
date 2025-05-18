#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct Line** create_line_ptrs_array(void) {

    struct Line** lines = malloc(sizeof(*lines));
    add_a_new_line(lines, 0);
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

void end_program(struct Line** lines, int num_of_lines) {
    for (int i = 0; i < num_of_lines; i++) {
        free(lines[i]->first_symbol);
        free(lines[i]);
    }
    free(lines);
    exit(0);
}