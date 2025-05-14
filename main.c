#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"


int main(void) {
    print_help();
    struct Line** lines = create_line_ptrs_array();
    int  line_ptrs_filled = 1;
    int  line_ptrs_array_capacity = 1;

    while (1) {
        int command_num;
        printf("Type a number of a command: ");
        int command_detected = scanf("%d", &command_num);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        char filename[100];

        if (command_detected != 1) {
            print_help();
            continue;
        }

        switch (command_num) {
            case 1:
                // insert_text_on_index(line_ptrs_filled-1, lines[line_ptrs_filled-1]->filled, lines, stdin);
                append_to_the_end(lines,  line_ptrs_filled);
                break;
            case 2:
                if (line_ptrs_filled >= line_ptrs_array_capacity) {
                    lines = alloc_more_ptrs_in_array(lines, line_ptrs_array_capacity);
                    line_ptrs_array_capacity *= 2;
                }
                add_a_new_line(lines, line_ptrs_filled);
                line_ptrs_filled += 1;
                printf("New line started \n");
                // insert_text_on_index(line_ptrs_filled-1, lines[line_ptrs_filled-1]->filled, lines, stdin);
                append_to_the_end(lines,  line_ptrs_filled);
                break;
            case 3:
                printf("Enter filename (no spaces): ");
                scanf("%99s", filename);
                while ((ch = getchar()) != '\n' && ch != EOF);
                save_to_file(filename, lines, line_ptrs_filled);
                break;
            case 4:
                printf("Enter filename (no spaces): ");
                scanf("%99s", filename);
                while ((ch = getchar()) != '\n' && ch != EOF);

                FILE *file = fopen(filename, "r");
                if (file != NULL)
                {
                    char buff [1000];
                    while (fgets(buff, sizeof(buff), file)) {

                        size_t line_length = strlen(buff) - 1;
                        if (buff[line_length] == '\n') {
                            buff[line_length] = '\0';
                        }
                        if (line_ptrs_filled >= line_ptrs_array_capacity) {
                            lines = alloc_more_ptrs_in_array(lines, line_ptrs_array_capacity);
                            line_ptrs_array_capacity *= 2;
                        }
                        add_a_new_line(lines, line_ptrs_filled);
                        insert_text_on_index(line_ptrs_filled, 0, lines, buff, line_length);
                        line_ptrs_filled += 1;
                    }

                    fclose(file);
                }
                else printf("Can't open such a file... Check filename \n");
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
                    printf("%d line consist of only %d symbols\n", line_index, lines[line_index]->filled);
                    continue;
                }
                while ((ch = getchar()) != '\n' && ch != EOF);

                char buff[1000];
                printf("Type a text to append: ");
                fgets(buff, sizeof(buff), stdin);
                size_t append_length = strlen(buff) - 1;

                if (buff[append_length] == '\n') {
                    buff[append_length] = '\0';
                }
                insert_text_on_index(line_index, symbol_index, lines, buff, append_length);
                break;
            case 7:
                // char buff[1000];
                printf("Type a text to search: ");
                fgets(buff, sizeof(buff), stdin);
                size_t search_length = strlen(buff) - 1;

                if (buff[search_length] == '\n') {
                    buff[search_length] = '\0';
                }
                search_substring(buff, lines, search_length, line_ptrs_filled);
                break;
        }
    }
    return 0;
}