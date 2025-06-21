//
// Created by Yulia Mala on 21.06.2025.
//

#ifndef USERCOMMANDS_H
#define USERCOMMANDS_H
#include <string>
#include <vector>

namespace UserCommands {
    const int INSERT_TEXT_ON_CURSOR = 1;
    const int ADD_NEW_CHAR_LINE = 2;
    const int SAVE_TO_FILE = 3;
    const int LOAD_FROM_FILE = 4;
    const int PRINT_TO_CONSOLE = 5;
    const int MOVE_CURSOR = 6;
    const int INSERT_WITH_REPLACEMENT = 7;
    const int SEARCH_TEXT = 8;
    const int DELETE_TEXT = 9;
    const int CUT = 10;
    const int COPY = 11;
    const int PASTE = 12;
    const int UNDO = 13;
    const int REDO = 14;
    const int ADD_CONTACT = 15;
    const int ADD_TASK = 16;
    const int ENCRYPT_ALL = 17;
    const int DECRYPT_ALL = 18;
    const int DELETE_LINE_OBJ = 19;
    const int CHANGE_TASK_STATUS = 20;
    const int END_PROGRAM = 21;

}

struct CommandInfo {
    int id;
    std::string description;
};

extern std::vector<CommandInfo> commands;


#endif //USERCOMMANDS_H
