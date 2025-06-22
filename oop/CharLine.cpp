//
// Created by Yulia Mala on 20.06.2025.
//

#include "CharLine.h"
#include <fstream>



CharArray* CharLine::str_repr_ptr() {
    return char_arr_ptr;
}

void CharLine::serialize_to_file(std::ofstream &file) const {
    file.write("TEXT", 4);
    int32_t text_len = char_arr_ptr->length();
    file.write(reinterpret_cast<const char*>(&text_len), sizeof(text_len));
    file.write(char_arr_ptr->symbols_ptr, text_len);
}

CharLine::CharLine(std::ifstream &file) {
    int32_t text_len;
    file.read(reinterpret_cast<char*>(&text_len), sizeof(text_len));

    if (text_len > 0) {
        char* temp = new char[text_len];
        file.read(temp, text_len);
        char_arr_ptr->append(temp, text_len);
        delete[] temp;
    }
}
