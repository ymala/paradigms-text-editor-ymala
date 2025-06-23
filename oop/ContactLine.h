//
// Created by Yulia Mala on 20.06.2025.
//

#ifndef СONTACTLINE_H
#define СONTACTLINE_H
#include "Line.h"


class ContactLine : public Line {
public:
    ContactLine(char *in_name, char *in_email);
    explicit ContactLine(std::ifstream& file);
    CharArray *name = new CharArray();
    CharArray *email = new CharArray();
    CharArray *str_repr_ptr() override;
    void serialize_to_file(std::ofstream& file) const override;
    std::vector<CharArray*> get_text_fields() override;
private:
    CharArray *repr = new CharArray();;
};



#endif //СONTACTLINE_H
