//
// Created by Yulia Mala on 28.05.2025.
//

#include "TextEditor.h"

#include "CharLine.h"
#include "TaskLine.h"
#include "UserCommands.h"

TextEditor::TextEditor() {
    CharLine* first_line_ptr = new CharLine;
    line_ptrs.insert_on_index(0, first_line_ptr);
}

TextEditor::~TextEditor() {
    delete buffer;

    while (!done_cmds_stack.empty()) {
        delete done_cmds_stack.top();
        done_cmds_stack.pop();
    }
    while (!canceled_cmds_stack.empty()) {
        delete canceled_cmds_stack.top();
        canceled_cmds_stack.pop();
    }
}

int TextEditor::get_cursor_line_index() const {
    return cursor.line_index;
}

int TextEditor::get_cursor_symbol_index() const {
    return cursor.symbol_index;
}

int TextEditor::get_num_of_lines() const {
    return line_ptrs.length();
}

int TextEditor::get_num_of_symbols_from_cursor_to_end_of_line() const {
    int line_length = cursor.symbol_index;

    Line *line_ptr = line_ptrs.get(cursor.line_index);
    CharLine* char_line_ptr = dynamic_cast<CharLine*>(line_ptr);

    if (char_line_ptr != nullptr) {
        line_length = char_line_ptr->char_arr_ptr->length();
    }
    return line_length - cursor.symbol_index;
}

bool TextEditor::execute_cmd(Command *cmd_ptr) {
    if (cmd_ptr->execute()) {
        done_cmds_stack.push(cmd_ptr);
        return true;
    }
    return false;
}

bool TextEditor::undo() {
    if (done_cmds_stack.empty()) {
        printf("There is nothing to undo\n");
        return false;
    }
    Command *last_cmd = done_cmds_stack.top();
    done_cmds_stack.pop();

    if (last_cmd->undo()) {
        canceled_cmds_stack.push(last_cmd);

        AddLineCommand* add_cmd = dynamic_cast<AddLineCommand*>(last_cmd);
        InsertCommand* insert_cmd = dynamic_cast<InsertCommand*>(last_cmd);

        if (add_cmd != nullptr) {
            move_cursor(add_cmd->line_index, add_cmd->symbol_index);
        }
        if (insert_cmd != nullptr) {
            move_cursor(insert_cmd->line_index, insert_cmd->symbol_index);
        }
        return true;
    }
    return false;
}

bool TextEditor::redo() {
    if (canceled_cmds_stack.empty()) {
        printf("There is nothing to redo");
        return false;
    }
    Command *last_canceled_cmd = canceled_cmds_stack.top();
    canceled_cmds_stack.pop();

    if (last_canceled_cmd->execute()) {
        done_cmds_stack.push(last_canceled_cmd);

        AddLineCommand* add_cmd = dynamic_cast<AddLineCommand*>(last_canceled_cmd);
        InsertCommand* insert_cmd = dynamic_cast<InsertCommand*>(last_canceled_cmd);

        if (add_cmd != nullptr) {
            move_cursor(add_cmd->line_index + 1, 0);
        }
        if (insert_cmd != nullptr) {
            move_cursor(
                insert_cmd->line_index,
                insert_cmd->symbol_index + insert_cmd->length_to_insert
                );
        }
        return true;
    }
    return false;
}

void TextEditor::move_cursor(int line_index, int symbol_index) {
    if (line_index > line_ptrs.length() - 1) {
        printf("Can't move to line %d with 0-based index. Only %d lines",
            line_index, line_ptrs.length()
            );
        return;
    }

    Line *line_ptr = line_ptrs.get(line_index);
    CharLine* char_line_ptr = dynamic_cast<CharLine*>(line_ptr);

    if (char_line_ptr == nullptr) {
        symbol_index = line_ptr->str_repr_ptr()->length();
    }
    else {
        int line_length = char_line_ptr->char_arr_ptr->length();

        if (symbol_index > line_length) {
            printf("Can't move to symbol %d with 0-based index. Only %d symbols",
                symbol_index, line_length
        );
            return;
        }
    }

    cursor.line_index = line_index;
    cursor.symbol_index = symbol_index;
    printf("Cursor moved to %d %d\n", line_index, symbol_index);

}

void TextEditor::add_char_line() {
    Command *cmd = new AddLineCommand(
        cursor.line_index, cursor.symbol_index, line_ptrs
        );
    if (cmd->execute()) {
        done_cmds_stack.push(cmd);
        move_cursor(cursor.line_index + 1, 0);
    }
}

void TextEditor::save_to_file(char *filename) const {
    FILE *file = fopen(filename, "w");
    if (file != nullptr)
    {
        int num_lines = get_num_of_lines();
        for (int i = 0; i < num_lines; i++) {
            fwrite(
                line_ptrs.get(i)->str_repr_ptr(),
                sizeof(char),
                line_ptrs.get(i)->str_repr_ptr()->length(),
                file
                );
            fputc('\n', file);
        }
        fclose(file);
        return;
    }
    printf("Can't open such a file... Try another filename \n");
}

void TextEditor::load_from_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != nullptr)
    {
        char buff [1000];
        while (fgets(buff, sizeof(buff), file)) {

            size_t line_length = strlen(buff);
            if (line_length > 0 && buff[line_length - 1] == '\n') {
                buff[line_length - 1] = '\0';
                line_length--;
            }

            auto* new_line_ptr = new CharLine;
            new_line_ptr->char_arr_ptr->append(buff, line_length);
            line_ptrs.insert_on_index(
                line_ptrs.length(), new_line_ptr
                );
        }
        fclose(file);
        move_cursor(line_ptrs.length() - 1, 0);
        return;
    }
    printf("Can't open such a file... Check filename \n");
}

void TextEditor::print_to_console() const {
    for (int i = 0; i < line_ptrs.length(); i++) {
        printf("%s \n", line_ptrs.get(i)->str_repr_ptr()->symbols_ptr);
    }
}

void TextEditor::insert_text(int length_to_insert, char *text_to_insert) {
    CharLine *current_line = dynamic_cast<CharLine*>(line_ptrs.get(cursor.line_index));

    Command *cmd = new InsertCommand(
        cursor.line_index,
        cursor.symbol_index,
        current_line->char_arr_ptr,
        length_to_insert,
        text_to_insert
        );
    if (cmd->execute()) {
        done_cmds_stack.push(cmd);
        move_cursor(
            cursor.line_index,
            cursor.symbol_index + length_to_insert
            );
    }
}

void TextEditor::search_text(int length_to_search, char *text_to_search) const {
    for (int i = 0; i < line_ptrs.length(); i++) {
        for (int j = 0; j <= line_ptrs.get(i)->str_repr_ptr()->length() - length_to_search; j++) {
            if (memcmp(
                text_to_search,
                line_ptrs.get(i)->str_repr_ptr()->symbols_ptr + j,
                length_to_search)
                == 0) {
                printf("line %d, symbol %d (0-based indexes)\n", i, j);
                }
        }
    }
}

void TextEditor::delete_text(int length_to_delete) {
    CharLine *current_line = dynamic_cast<CharLine*>(line_ptrs.get(cursor.line_index));

    Command *cmd = new DeleteCommand(
        cursor.symbol_index,
        length_to_delete,
        current_line->char_arr_ptr
        );
    if (cmd->execute()) {
        done_cmds_stack.push(cmd);
        printf("Delete %d symbols from cursor..\n", length_to_delete);

    }
}

void TextEditor::copy(int length_to_copy) {
    CharLine *current_line = dynamic_cast<CharLine*>(line_ptrs.get(cursor.line_index));

    char *text_to_copy = current_line->char_arr_ptr->get_substring(
        cursor.symbol_index, length_to_copy
        );
    buffer->append(text_to_copy, length_to_copy);
    printf("Copy %d symbols from cursor..\n", length_to_copy);

}

void TextEditor::paste() {
    if (buffer->length() == 0) {
        printf("Nothing has been copied\n");
        return;
    }
    insert_text(buffer->length(), buffer->symbols_ptr);
    printf("Paste on cursor..\n");
}

bool TextEditor::validate_user_cmd(int cmd_num) {
    if (cmd_num == UserCommands::ADD_CONTACT
        || cmd_num == UserCommands::ADD_NEW_CHAR_LINE
        || cmd_num == UserCommands::ADD_TASK
        || cmd_num == UserCommands::DECRYPT_ALL
        || cmd_num == UserCommands::ENCRYPT_ALL
        || cmd_num == UserCommands::DELETE_LINE_OBJ
        || cmd_num == UserCommands::MOVE_CURSOR
        || cmd_num == UserCommands::LOAD_FROM_FILE
        || cmd_num == UserCommands::SAVE_TO_FILE
        || cmd_num == UserCommands::PRINT_TO_CONSOLE
        || cmd_num == UserCommands::UNDO
        || cmd_num == UserCommands::REDO
        || cmd_num == UserCommands::SEARCH_TEXT
        || cmd_num == UserCommands::END_PROGRAM) {
            return true;
    }

    Line *line_ptr = line_ptrs.get(cursor.line_index);
    CharLine* char_line_ptr = dynamic_cast<CharLine*>(line_ptr);
    TaskLine* task_line_ptr = dynamic_cast<TaskLine*>(line_ptr);

    if ((char_line_ptr != nullptr) &&
        (cmd_num == UserCommands::INSERT_TEXT_ON_CURSOR
            || cmd_num == UserCommands::INSERT_WITH_REPLACEMENT
            || cmd_num == UserCommands::DELETE_TEXT
            || cmd_num == UserCommands::CUT
            || cmd_num == UserCommands::COPY
            || cmd_num == UserCommands::PASTE
            )) {
        return true;
    }

    if (task_line_ptr != nullptr && cmd_num == UserCommands::CHANGE_TASK_STATUS) {
        return true;
    }

    return false;
}

