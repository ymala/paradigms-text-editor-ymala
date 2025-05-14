#ifndef HEADER_H
#define HEADER_H

#define INITIAL_LINE_CAPACITY 100

void print_help(void);

struct Line** create_line_ptrs_array(void);

void alloc_more_symbols_in_line(struct Line*);

void append_to_the_end(struct Line **lines, int num_of_lines);

void add_a_new_line(struct Line** lines, int num_of_lines);

struct Line** alloc_more_ptrs_in_array(struct Line** lines, int line_ptrs_array_capacity);

void print_current_text(struct Line** lines, int num_of_lines);

void insert_text_on_index(int line_index, int symbol_index, struct Line** lines, char* source, int append_length);

void search_substring(
    char* str_to_search,
    struct Line** lines,
    int length_to_search,
    int num_of_lines
    );

void save_to_file(char* filename, struct Line** lines, int num_of_lines);

void load_from_file(char* filename, struct Line** lines, int num_of_lines);

struct Line {
    char *first_symbol;
    int capacity;
    int filled;
};

#endif //HEADER_H
