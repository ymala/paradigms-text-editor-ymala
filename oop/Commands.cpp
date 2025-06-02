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
    char *in_text_to_insert
    ) :
line_index(line_index),
symbol_index(symbol_index),
length_to_insert(length_to_insert),
string_ptr(string_ptr)
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
    CharPointerArray &line_ptrs
    ): line_index(line_index),
       symbol_index(symbol_index),
       line_ptrs(line_ptrs) {

    int num_ptrs_after_new_line = line_ptrs.length() - (line_index + 1);
    ptrs_after_new_line = line_ptrs.get_subsequence(
        line_index + 1, num_ptrs_after_new_line
    );

    line_before_new_ptr = line_ptrs.get(line_index);
    num_symbols_pushed_to_new_line = line_before_new_ptr->length() - symbol_index;
    symbols_pushed_to_new_line = line_before_new_ptr->get_substring(
        symbol_index, num_symbols_pushed_to_new_line
    );
}

AddLineCommand::~AddLineCommand() {
    free(ptrs_after_new_line);
    free(symbols_pushed_to_new_line);
    delete new_line_ptr;
}

bool AddLineCommand::execute() {
    if (executed) {
        throw std::logic_error("Cannot execute a command that has been already executed.\n");
    }
    new_line_ptr->append(
        symbols_pushed_to_new_line, num_symbols_pushed_to_new_line
        );
    line_before_new_ptr->delete_on_index(
        num_symbols_pushed_to_new_line, symbol_index
        );

    line_ptrs.insert_on_index(line_index + 1, new_line_ptr);

    executed = true;
    return true;
}

bool AddLineCommand::undo() {
    if (not executed) {
        throw std::logic_error("Cannot undo a command that hasn't been executed.\n");
    }
    line_before_new_ptr->append(
        symbols_pushed_to_new_line, num_symbols_pushed_to_new_line
        );
    line_ptrs.delete_ptr(line_index + 1);
    executed = false;
    return true;
}
