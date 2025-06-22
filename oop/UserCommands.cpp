#include "UserCommands.h"

#include <vector>
//
// Created by Yulia Mala on 21.06.2025.
//
std::vector<CommandInfo> commands = {
    {UserCommands::INSERT_TEXT_ON_CURSOR,    "Insert on cursor"},
    {UserCommands::ADD_NEW_CHAR_LINE,        "Start new char line"},
    {UserCommands::SAVE_TO_FILE,             "Save to file"},
    {UserCommands::LOAD_FROM_FILE,           "Load from file"},
    {UserCommands::PRINT_TO_CONSOLE,         "Print to console"},
    {UserCommands::MOVE_CURSOR,              "Move cursor"},
    {UserCommands::INSERT_WITH_REPLACEMENT,  "Insert with replacement"},
    {UserCommands::SEARCH_TEXT,              "Search text"},
    {UserCommands::DELETE_TEXT,              "Delete text"},
    {UserCommands::CUT,                      "Cut"},
    {UserCommands::COPY,                     "Copy"},
    {UserCommands::PASTE,                    "Paste"},
    {UserCommands::UNDO,                     "Undo"},
    {UserCommands::REDO,                     "Redo"},
    {UserCommands::ADD_CONTACT,              "Add contact"},
    {UserCommands::ADD_TASK,                 "Add task"},
    {UserCommands::ENCRYPT_ALL,              "Encrypt all data"},
    {UserCommands::DECRYPT_ALL,              "Decrypt all data"},
    {UserCommands::DELETE_LINE_OBJ,          "Delete current line object (except 1st line)"},
    {UserCommands::CHANGE_TASK_STATUS,       "Change task status"},
    {UserCommands::END_PROGRAM,              "End program"}
};
