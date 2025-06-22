//
// Created by Yulia Mala on 20.06.2025.
//

#ifndef TASKLINE_H
#define TASKLINE_H
#include "Line.h"


class TaskLine : public Line {
public:
    explicit TaskLine(char *in_description);
    explicit TaskLine(std::ifstream& file);
    bool status = false;
    CharArray *description = new CharArray();
    void serialize_to_file(std::ofstream& file) const override;
    CharArray *str_repr_ptr() override;

private:
    CharArray *done_displ = new CharArray();
    CharArray *undone_displ = new CharArray();
    void status_dispr_fill();
};



#endif //TASKLINE_H
