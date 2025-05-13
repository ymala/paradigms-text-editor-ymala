#include <stdio.h>
#include <stdlib.h>
#include "header.h"


int main(void) {
    print_help();
    struct Line** lines = create_line_ptrs_array();
    int  line_ptrs_filled = 1;
    int  line_ptrs_array_capacity = 1;

    while (1) {
        int command_num;
        printf("Type a number of a command: \n");
        int command_detected = scanf("%d", &command_num);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        if (command_detected != 1) {
            print_help();
            continue;
        }

        switch (command_num) {
            case 1:
                insert_text_on_index(line_ptrs_filled-1, lines[line_ptrs_filled-1]->filled, lines);
                // append_to_the_end(lines,  line_ptrs_filled);
                break;
            case 2:
                if (line_ptrs_filled >= line_ptrs_array_capacity) {
                    lines = alloc_more_ptrs_in_array(lines, line_ptrs_array_capacity);
                    line_ptrs_array_capacity *= 2;
                }
                add_a_new_line(lines, line_ptrs_filled);
                line_ptrs_filled += 1;
                printf("New line started \n");
                append_to_the_end(lines,  line_ptrs_filled);
                break;
            case 3:
                // code block
                break;
            case 4:
                // code block
                break;
            case 5:
                print_current_text(lines,  line_ptrs_filled);
                break;
            case 6:
                int line_index;
                int symbol_index;
                printf("Enter line and index starts from 0 (for ex. 0 6): ");
                if (scanf("%d %d", &line_index, &symbol_index) != 2) {
                    printf("Invalid input. Two integers expected\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    continue;
                }
                if (line_ptrs_filled < line_index) {
                    printf("Yout text consist of only %d lines\n", line_ptrs_filled);
                    continue;
                }
                if (lines[line_index]->filled < symbol_index) {
                    printf("%d line consist of only %d symbols\n", line_ptrs_filled, lines[line_index]->filled);
                    continue;
                }
                while ((ch = getchar()) != '\n' && ch != EOF);
                insert_text_on_index(line_index, symbol_index, lines);
                break;
            case 7:
                // code block
                break;
        }
    }
    return 0;
}