//
// Created by Yulia Mala on 28.05.2025.
//

#include "TextEditor.h"

TextEditor::TextEditor() {
    CharArray* first_line_ptr = new CharArray;
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

bool TextEditor::execute_cmd(Command *cmd_ptr) {
    if (cmd_ptr->execute()) {
        done_cmds_stack.push(cmd_ptr);
        return true;
    }
    return false;
}

bool TextEditor::undo() {
    if (done_cmds_stack.empty()) {
        printf("There is nothing to undo");
        return false;
    }
    Command *last_cmd = done_cmds_stack.top();
    done_cmds_stack.pop();
    if (last_cmd->undo()) {
        canceled_cmds_stack.push(last_cmd);
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
    if (symbol_index > line_ptrs.get(line_index)->length() + 1) {
        printf("Can't move to line %d with 0-based index. Only %d lines",
            line_index, line_ptrs.length()
    );
        return;
    }
    cursor.line_index = line_index;
    cursor.symbol_index = symbol_index;
    printf("Cursor moved\n");

}

void TextEditor::start_line() {
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
                line_ptrs.get(i)->symbols_ptr,
                sizeof(char),
                line_ptrs.get(i)->length(),
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

            auto* new_line_ptr = new CharArray;
            new_line_ptr->append(buff, line_length); // NOLINT(*-narrowing-conversions)
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
        printf("%s \n", line_ptrs.get(i)->symbols_ptr);
    }
}

void TextEditor::insert_text(int length_to_insert, char *text_to_insert) {
    Command *cmd = new InsertCommand(
        cursor.symbol_index,
        line_ptrs.get(cursor.line_index),
        length_to_insert,
        text_to_insert
        );
    if (cmd->execute()) {
        done_cmds_stack.push(cmd);
        move_cursor(cursor.line_index, cursor.symbol_index + length_to_insert);
    }
}

void TextEditor::search_text(int length_to_search, char *text_to_search) const {
    for (int i = 0; i < line_ptrs.length(); i++) {
        for (int j = 0; j <= line_ptrs.get(i)->length() - length_to_search; j++) {
            if (memcmp(
                text_to_search,
                line_ptrs.get(i)->symbols_ptr + j,
                length_to_search)
                == 0) {
                printf("line %d, symbol %d (0-based indexes)\n", i, j);
                }
        }
    }
}

void TextEditor::delete_text(int length_to_delete) {
    Command *cmd = new DeleteCommand(
        cursor.symbol_index,
        length_to_delete,
        line_ptrs.get(cursor.line_index)
        );
    if (cmd->execute()) {
        done_cmds_stack.push(cmd);
        printf("Delete %d symbols from cursor..\n", length_to_delete);

    }
}

void TextEditor::copy(int length_to_copy) {
    char *text_to_copy = line_ptrs.get(cursor.line_index)->get_substring(
        cursor.symbol_index, length_to_copy
        );
    buffer->append(text_to_copy, length_to_copy);
    printf("Copy %d symbols from cursor..\n", length_to_copy);

}

void TextEditor::paste() {
    if (buffer->length() == 0) {
        printf("Nothing has been copied");
        return;
    }
    insert_text(buffer->length(), buffer->symbols_ptr);
    printf("Paste on cursor..\n");
}
