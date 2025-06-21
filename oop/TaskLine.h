//
// Created by Yulia Mala on 20.06.2025.
//

#ifndef TASKLINE_H
#define TASKLINE_H
#include "Line.h"


class TaskLine : public Line {
public:
    TaskLine();
    bool status = false;
    CharArray *description = new CharArray();
    CharArray *done_displ = new CharArray();
    CharArray *undone_displ = new CharArray();

    CharArray *str_repr_ptr() override;
};



#endif //TASKLINE_H
