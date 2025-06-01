#include <iostream>

#include "TextEditor.h"
#include "utils.h"


int main() {
    print_help();
    TextEditor *editor = new TextEditor;

    while (true) {
        int command_num;
        printf("Type a number of a command: ");
        int command_detected = scanf("%d", &command_num);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        if (command_detected != 1) {
            print_help();
            continue;
        }

        int text_length = 0;
        int *text_length_ptr = &text_length;

        switch (command_num) {
            case 1: {
                printf("Add on cursor. ");
                char *text = get_text_from_user(text_length_ptr);
                editor->insert_text(text_length, text);
                free(text);
                break;
            }
            case 2:
                editor->start_line();
                printf("New line started\n");
                break;
            case 3: {
                printf("Name of file? ");
                char *filename = get_text_from_user();
                editor->save_to_file(filename);
                free(filename);
                break;
            }
            case 4: {
                printf("Name of file? ");
                char *filename = get_text_from_user();
                editor->load_from_file(filename);
                free(filename);
                break;
            }
            case 5:
                editor->print_to_console();
                break;
            case 6: {
                int line_index;
                int symbol_index;
                get_index_from_user(line_index, symbol_index);
                editor->move_cursor(line_index, symbol_index);
                break;
            }
            case 7: {
                printf("Insert with replacement..");
                char *text = get_text_from_user(text_length_ptr);
                editor->insert_text(text_length, text);
                editor->delete_text(text_length);
                free(text);
                break;
            }
            case 8: {
                printf("What to look for? ");
                char *text = get_text_from_user(text_length_ptr);
                editor->search_text(text_length, text);
                free(text);
                break;
            }
            case 9: {
                printf("How many symbols to delete? ");
                int length_to_delete = get_length_from_user();
                editor->delete_text(length_to_delete);
                break;
            }
            case 10: {
                printf("How many symbols to cut? ");
                int length_to_cut = get_length_from_user();
                editor->copy(length_to_cut);
                editor->delete_text(length_to_cut);
                break;
            }
            case 11: {
                printf("How many symbols to copy? ");
                int length_to_copy = get_length_from_user();
                editor->copy(length_to_copy);
                break;
            }
            case 12: {
                editor->paste();
                break;
            }
            case 13: {
                editor->undo();
                break;
            }
            case 14: {
                editor->redo();
                break;
            }
            case 15:
                end_program(editor);
                break;
        }
    }
    return 0;
}
