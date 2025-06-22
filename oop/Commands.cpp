//
// Created by Yulia Mala on 29.05.2025.
//

#include "Commands.h"

#include <cstring>
#include <stdexcept>

InsertCommand::InsertCommand(
    int  line_index,
    int  symbol_index,
    CharArray *string_ptr,
    int length_to_insert,
    char *in_text_to_insert,
    int &ref_cursor_symbol
    ) :
line_index(line_index),
symbol_index(symbol_index),
length_to_insert(length_to_insert),
string_ptr(string_ptr),
ref_cursor_symbol(ref_cursor_symbol)
 {
     text_to_insert = (char*)malloc(length_to_insert);
     std::memcpy(text_to_insert, in_text_to_insert, length_to_insert);
 }

bool InsertCommand::execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.\n");
    }
    string_ptr->insert_on_index(text_to_insert, length_to_insert, symbol_index);
    executed = true;
    return true;
}

bool InsertCommand::undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.\n");
    }
    string_ptr->delete_on_index(length_to_insert, symbol_index);
    ref_cursor_symbol = symbol_index;
    executed = false;
    return true;
}

InsertCommand::~InsertCommand() {
    free(text_to_insert);
}

DeleteCommand::DeleteCommand(
    int index,
    int length_to_delete,
    CharArray *string_ptr
    ):
symbol_index(index),
length_to_delete(length_to_delete),
string_ptr(string_ptr) {
    deleted_text = string_ptr->get_substring(index, length_to_delete);
}

DeleteCommand::~DeleteCommand() {
    free(deleted_text);
}

bool DeleteCommand::execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.\n");
    }
    string_ptr->delete_on_index(length_to_delete, symbol_index);
    executed = true;
    return true;
}

bool DeleteCommand::undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.\n");
    }
    string_ptr->insert_on_index(deleted_text, length_to_delete, symbol_index);
    executed = false;
    return true;
}

AddLineCommand::AddLineCommand(
    int line_index,
    int symbol_index,
    LinePointerArray &line_ptrs,
    CharLine *new_line_ptr,
    int &ref_cursor_line,
    int &ref_cursor_symbol
    ): line_index(line_index),
        symbol_index(symbol_index),
        line_ptrs(line_ptrs),
        new_line_ptr(new_line_ptr),
        ref_cursor_symbol(ref_cursor_symbol),
        ref_cursor_line(ref_cursor_line) {

    line_before_new_ptr = line_ptrs.get(line_index);

    CharLine *char_line_before_new = dynamic_cast<CharLine *>(line_before_new_ptr);
    if (char_line_before_new != nullptr) {
        num_symbols_pushed_to_new_line = char_line_before_new->char_arr_ptr->length() - symbol_index;
        symbols_pushed_to_new_line = char_line_before_new->char_arr_ptr->get_substring(
            symbol_index, num_symbols_pushed_to_new_line
        );
    } else {
        static char dummy = '\0';
        num_symbols_pushed_to_new_line = 0;
        symbols_pushed_to_new_line = &dummy;
    }
}

AddLineCommand::~AddLineCommand() {
    free(symbols_pushed_to_new_line);
    delete new_line_ptr;
}

bool AddLineCommand::execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.\n");
    }
    new_line_ptr->char_arr_ptr->clear();

    new_line_ptr->char_arr_ptr->append(
        symbols_pushed_to_new_line, num_symbols_pushed_to_new_line
        );

    CharLine *char_line_before_new = dynamic_cast<CharLine *>(line_before_new_ptr);
    if (char_line_before_new != nullptr) {
        char_line_before_new->char_arr_ptr->delete_on_index(
        num_symbols_pushed_to_new_line, symbol_index
        );
    }
    line_ptrs.insert_on_index(line_index + 1, new_line_ptr);

    ref_cursor_line = line_index + 1;
    ref_cursor_symbol = 0;

    executed = true;
    return true;
}

bool AddLineCommand::undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.\n");
    }
    CharLine *char_line_before_new = dynamic_cast<CharLine *>(line_before_new_ptr);
    if (char_line_before_new != nullptr) {
        char_line_before_new->char_arr_ptr->append(
            symbols_pushed_to_new_line, num_symbols_pushed_to_new_line
            );
    }
    line_ptrs.extract_ptr(line_index + 1);
    ref_cursor_line = line_index;
    ref_cursor_symbol = symbol_index;
    executed = false;
    return true;
}


AddObjCommand::AddObjCommand(
    int line_index,
    LinePointerArray &line_ptrs,
    Line *obj_ptr,
    int &ref_cursor_line
    ) : line_index(line_index),
        line_ptrs(line_ptrs),
        obj_ptr(obj_ptr),
        ref_cursor_line(ref_cursor_line) {
}

AddObjCommand::~AddObjCommand() {
    delete obj_ptr;
}

bool AddObjCommand::execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.\n");
    }
    line_ptrs.insert_on_index(line_index + 1, obj_ptr);
    ref_cursor_line = line_index + 1;

    executed = true;
    return true;
}

bool AddObjCommand::undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.\n");
    }
    line_ptrs.extract_ptr(line_index + 1);
    ref_cursor_line = line_index;
    executed = false;
    return true;
}

DeleteLineObj::DeleteLineObj(
    int line_index,
    LinePointerArray &line_ptrs,
    int &ref_cursor_line
    ): line_index(line_index),
        line_ptrs(line_ptrs),
        ref_cursor_line(ref_cursor_line) {}

bool DeleteLineObj::execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.\n");
    }
    obj_ptr = line_ptrs.get(line_index);
    line_ptrs.extract_ptr(line_index);
    ref_cursor_line = line_index - 1;

    executed = true;
    return true;
}

bool DeleteLineObj::undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.\n");
    }
    line_ptrs.insert_on_index(line_index, obj_ptr);
    ref_cursor_line = line_index + 1;
    executed = false;
    return true;
}



