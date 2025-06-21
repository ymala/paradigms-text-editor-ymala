//
// Created by Yulia Mala on 20.06.2025.
//

#ifndef LINE_H
#define LINE_H
#include "CharArray.h"


class Line {
public:
    virtual ~Line() = default;
    virtual CharArray *str_repr_ptr() = 0;
};



#endif //LINE_H
