//
// Created by Yulia Mala on 20.06.2025.
//

#include "TaskLine.h"

#include <string>

TaskLine::TaskLine() {
    char undone[] = "[   ]   ";
    undone_displ->append(undone, strlen(undone));

    char done[] = "[ * ]   ";
    done_displ->append(done, strlen(done));
}


CharArray* TaskLine::str_repr_ptr() {
    CharArray* box = status ?  done_displ : undone_displ;

    CharArray *repr = new CharArray();
    repr->append(box->symbols_ptr, box->length());
    repr->append(description->symbols_ptr, description->length());

    return repr;
}


