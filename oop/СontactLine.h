//
// Created by Yulia Mala on 20.06.2025.
//

#ifndef СONTACTLINE_H
#define СONTACTLINE_H
#include "Line.h"


class СontactLine : public Line {
public:
    CharArray *name = new CharArray();
    CharArray *email = new CharArray();

    CharArray *str_repr_ptr() override;
};



#endif //СONTACTLINE_H
