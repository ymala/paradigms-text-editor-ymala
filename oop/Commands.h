//
// Created by Yulia Mala on 29.05.2025.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include "CharArray.h"
#include "CharPointerArray.h"

class Command {
public:
    virtual ~Command() = default;
    virtual bool execute() = 0;
    virtual bool undo() = 0;
};


class InsertCommand : public Command {
public:
    InsertCommand(
        int index,
        CharArray *string_ptr,
        int length_to_insert,
        char *in_text_to_insert);

    ~InsertCommand() override;
    bool execute() override;
    bool undo() override;
    bool executed = false;
private:
    int index;
    int length_to_insert;
    CharArray* string_ptr;
    char *text_to_insert;
};


class DeleteCommand : public Command {
public:
    DeleteCommand(int index, int length_to_delete, CharArray* string_ptr);
    ~DeleteCommand() override;
    bool execute() override;
    bool undo() override;
    bool executed = false;
private:
    int const index;
    int const length_to_delete;
    CharArray* string_ptr;
    char *deleted_text;

};


class AddLineCommand : public Command {
public:
    AddLineCommand(int line_index, int symbol_index, CharPointerArray &line_ptrs);
    ~AddLineCommand() override;
    bool execute() override;
    bool undo() override;
    bool executed = false;
private:
    int const line_index;
    int const symbol_index;
    CharPointerArray &line_ptrs;
    CharArray **ptrs_after_new_line;
    char* symbols_pushed_to_new_line;
    int num_symbols_pushed_to_new_line;
    CharArray* new_line_ptr = new CharArray;
    CharArray* line_before_new_ptr;
};

#endif //COMMANDS_H
