#include <iostream>

#include "TextEditor.h"
#include "UserCommands.h"
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

        bool allowed = editor->validate_user_cmd(command_num);

        if (!allowed) {
            printf("Command couldn't be applied to the current line type\n");
            continue;
        }

        switch (command_num) {
            case UserCommands::INSERT_TEXT_ON_CURSOR: {
                printf("Add on cursor. ");
                char *text = get_text_from_user(text_length_ptr);
                editor->insert_text(text_length, text);
                free(text);
                break;
            }
            case UserCommands::ADD_NEW_CHAR_LINE:
                editor->add_char_line();
                printf("New line started\n");
                break;
            case UserCommands::SAVE_TO_FILE: {
                printf("Name of file? ");
                char *filename = get_text_from_user();
                editor->save_obj_to_file(filename);
                free(filename);
                break;
            }
            case UserCommands::LOAD_FROM_FILE: {
                printf("Name of file? ");
                char *filename = get_text_from_user();
                editor->load_obj_from_file(filename);
                free(filename);
                break;
            }
            case UserCommands::PRINT_TO_CONSOLE:
                editor->print_to_console();
                break;
            case UserCommands::MOVE_CURSOR: {
                int line_index;
                int symbol_index;
                get_index_from_user(line_index, symbol_index);
                editor->move_cursor(line_index, symbol_index);
                break;
            }
            case UserCommands::INSERT_WITH_REPLACEMENT: {
                printf("Insert with replacement..");

                int num_of_symbols_to_end = editor->get_num_of_symbols_from_cursor_to_end_of_line();
                char *text = get_text_from_user(text_length_ptr);
                editor->insert_text(text_length, text);
                editor->delete_text(std::min(num_of_symbols_to_end, text_length));
                free(text);
                break;
            }
            case UserCommands::SEARCH_TEXT: {
                printf("What to look for? ");
                char *text = get_text_from_user(text_length_ptr);
                editor->search_text(text_length, text);
                free(text);
                break;
            }
            case UserCommands::DELETE_TEXT: {
                printf("How many symbols to delete? ");
                int length_to_delete = get_length_from_user();
                editor->delete_text(length_to_delete);
                break;
            }
            case UserCommands::CUT: {
                printf("How many symbols to cut? ");
                int length_to_cut = get_length_from_user();
                editor->copy(length_to_cut);
                editor->delete_text(length_to_cut);
                break;
            }
            case UserCommands::COPY: {
                printf("How many symbols to copy? ");
                int length_to_copy = get_length_from_user();
                editor->copy(length_to_copy);
                break;
            }
            case UserCommands::PASTE: {
                editor->paste();
                break;
            }
            case UserCommands::UNDO: {
                editor->undo();
                break;
            }
            case UserCommands::REDO: {
                editor->redo();
                break;
            }
            case UserCommands::ADD_CONTACT: {
                printf("Contact name?\n");
                char *name = get_text_from_user(text_length_ptr);
                printf("Contact email?\n");
                char *email = get_text_from_user(text_length_ptr);

                editor->add_contact(name, email);
                break;
            }
            case UserCommands::ADD_TASK: {
                printf("Task description?\n");
                char *descr = get_text_from_user(text_length_ptr);
                editor->add_task(descr);
                break;
            }

            case UserCommands::DELETE_LINE_OBJ: {
                editor->delete_line_obj();
                break;;
            }

            case UserCommands::ENCRYPT_ALL: {
                printf("Key?\n");
                int key = get_length_from_user();
                editor->encrypt_instance(key);
                break;
            }

            case UserCommands::DECRYPT_ALL: {
                printf("Key?\n");
                int key = get_length_from_user();
                editor->decrypt_instance(key);
                break;
            }

            case UserCommands::CHANGE_TASK_STATUS: {
                editor->change_task_status();
                break;
            }

            case UserCommands::END_PROGRAM:
                end_program(editor);
                // є якась проблема з делейтом
                break;
        }
    }
    return 0;
}
