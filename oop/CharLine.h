//
// Created by Yulia Mala on 20.06.2025.
//

#ifndef CHARLINE_H
#define CHARLINE_H
#include "CharArray.h"
#include "Line.h"


class CharLine : public Line {
public:
    CharLine() = default;
    explicit CharLine(std::ifstream& file);
    CharArray *char_arr_ptr = new CharArray();
    CharArray* str_repr_ptr() override;
    void serialize_to_file(std::ofstream& file) const override;
};



#endif //CHARLINE_H
