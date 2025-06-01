//
// Created by Yulia Mala on 28.05.2025.
//

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include <stack>

#include "Commands.h"
#include "utils.h"

class TextEditor {
public:
    TextEditor();
    ~TextEditor();
    int get_cursor_line_index() const;
    int get_cursor_symbol_index() const;
    int get_num_of_lines() const;
    bool execute_cmd(Command *cmd_ptr);
    bool undo();
    bool redo();
    void move_cursor(int line_index, int symbol_index);
    void start_line();
    void save_to_file(char *filename) const;
    void load_from_file(char *filename);
    void print_to_console() const;
    void insert_text(int length_to_insert, char *text_to_insert);
    void search_text(int length_to_search, char *text_to_search) const;
    void delete_text(int length_to_delete);
    void copy(int length_to_copy);
    void paste();


private:
    Cursor cursor;
    CharArray *buffer = new CharArray();
    CharPointerArray line_ptrs;
    std::stack<Command*> done_cmds_stack;
    std::stack<Command*> canceled_cmds_stack;

};

void end_program(TextEditor *editor);

#endif //TEXTEDITOR_H
