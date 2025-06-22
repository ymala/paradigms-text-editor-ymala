//
// Created by Yulia Mala on 20.06.2025.
//

#ifndef LINE_H
#define LINE_H
#include <iosfwd>

#include "CharArray.h"


class Line {
public:
    virtual ~Line() = default;
    virtual CharArray *str_repr_ptr() = 0;
    virtual void serialize_to_file(std::ofstream& file) const = 0;
};


#endif //LINE_H
