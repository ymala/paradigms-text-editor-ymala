//
// Created by Yulia Mala on 29.05.2025.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include "CharArray.h"
#include "CharLine.h"
#include "TaskLine.h"
#include "ContactLine.h"
#include "LinePointerArray.h"

class Command {
public:
    virtual ~Command() = default;
    virtual bool execute() = 0;
    virtual bool undo() = 0;
};


class InsertCommand : public Command {
public:
    InsertCommand(
        int line_index,
        int symbol_index,
        CharArray *string_ptr,
        int length_to_insert,
        char *in_text_to_insert,
        int &ref_cursor_symbol);

    ~InsertCommand() override;
    bool execute() override;
    bool undo() override;
    bool executed = false;
    int length_to_insert;
    int const line_index;
    int const symbol_index;
private:
    CharArray* string_ptr;
    char *text_to_insert;
    int &ref_cursor_symbol;

};


class DeleteCommand : public Command {
public:
    DeleteCommand(int index, int length_to_delete, CharArray* string_ptr);
    ~DeleteCommand() override;
    bool execute() override;
    bool undo() override;
    bool executed = false;
    int const symbol_index;
    int const length_to_delete;
private:
    CharArray* string_ptr;
    char *deleted_text;

};


class AddLineCommand : public Command {
public:
    AddLineCommand(
        int line_index,
        int symbol_index,
        LinePointerArray &line_ptrs,
        CharLine* new_line_ptr,
        int &ref_cursor_line,
        int &ref_cursor_symbol);

    ~AddLineCommand() override;
    bool execute() override;
    bool undo() override;
    bool executed = false;
    int const line_index;
    int const symbol_index;
private:
    LinePointerArray &line_ptrs;
    char* symbols_pushed_to_new_line;
    int num_symbols_pushed_to_new_line;
    CharLine* new_line_ptr;
    Line* line_before_new_ptr;
    int &ref_cursor_line;
    int &ref_cursor_symbol;

};


class AddObjCommand : public Command {
public:
    AddObjCommand(
        int line_index,
        LinePointerArray &line_ptrs,
        Line *obj_ptr,
        int &ref_cursor_line);

    ~AddObjCommand() override;
    bool execute() override;
    bool undo() override;
    bool executed = false;
    int const line_index;
private:
    LinePointerArray &line_ptrs;
    Line* obj_ptr;
    int &ref_cursor_line;
};

class DeleteLineObj : public Command {
public:
    DeleteLineObj(
    int line_index,
    LinePointerArray &line_ptrs,
    int &ref_cursor_line);
    bool execute() override;
    bool undo() override;
    bool executed = false;
    int const line_index;
private:
    LinePointerArray &line_ptrs;
    Line* obj_ptr;
    int &ref_cursor_line;
};


#endif //COMMANDS_H
