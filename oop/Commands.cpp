//
// Created by Yulia Mala on 29.05.2025.
//

#include "Commands.h"

#include <stdexcept>

InsertCommand::InsertCommand(
    int index,
    CharArray *string_ptr,
    int length_to_insert,
    char *text_to_insert
    ) :
index(index),
string_ptr(string_ptr),
length_to_insert(length_to_insert),
text_to_insert(text_to_insert)
 {}

bool InsertCommand::Execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.");
    }
    string_ptr->insert_on_index(text_to_insert, length_to_insert, index);
    executed = true;
    return true;
}

bool InsertCommand::Undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.");
    }
    string_ptr->delete_on_index(length_to_insert, index);
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
index(index),
length_to_delete(length_to_delete),
string_ptr(string_ptr) {
    deleted_text = string_ptr->get_substring(index, length_to_delete);
}

DeleteCommand::~DeleteCommand() {
    free(deleted_text);
}

bool DeleteCommand::Execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.");
    }
    string_ptr->delete_on_index(length_to_delete, index);
    executed = true;
    return true;
}

bool DeleteCommand::Undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.");
    }
    string_ptr->insert_on_index(deleted_text, length_to_delete, index);
    executed = false;
    return true;
}


AddLineCommand::AddLineCommand(
    int line_index,
    int symbol_index,
    CharPointerArray &char_pointer_array
    ): line_index(line_index),
       symbol_index(symbol_index),
       char_pointer_array(char_pointer_array) {

    int num_ptrs_after_new_line = char_pointer_array.length() - line_index;
    ptrs_after_new_line = char_pointer_array.get_subsequence(
        line_index, num_ptrs_after_new_line
    );

    line_before_new_ptr = char_pointer_array.get(line_index);
    num_symbols_pushed_to_new_line = line_before_new_ptr->length() - symbol_index;
    symbols_pushed_to_new_line = line_before_new_ptr->get_substring(
        symbol_index, num_symbols_pushed_to_new_line
    );
}

AddLineCommand::~AddLineCommand() {
    free(ptrs_after_new_line);
    free(symbols_pushed_to_new_line);
}

bool AddLineCommand::Execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.");
    }
    new_line_ptr->append(
        symbols_pushed_to_new_line, num_symbols_pushed_to_new_line
        );
    line_before_new_ptr->delete_on_index(
        num_symbols_pushed_to_new_line, symbol_index
        );

    char_pointer_array.insert_on_index(line_index, new_line_ptr);

    executed = true;
    return true;
}

bool AddLineCommand::Undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.");
    }
    line_before_new_ptr->append(
        symbols_pushed_to_new_line, num_symbols_pushed_to_new_line
        );
    char_pointer_array.delete_ptr(line_index);
    delete new_line_ptr;
    executed = false;
    return true;
}



