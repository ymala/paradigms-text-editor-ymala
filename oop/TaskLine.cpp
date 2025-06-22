//
// Created by Yulia Mala on 20.06.2025.
//

#include "TaskLine.h"

#include <fstream>
#include <string>

TaskLine::TaskLine(char *in_description) {
    description->append_null_term_str(in_description);
    status_dispr_fill();
}


CharArray* TaskLine::str_repr_ptr() {
    CharArray* box = status ?  done_displ : undone_displ;
    CharArray *repr = new CharArray();
    repr->append(box->symbols_ptr, box->length());
    repr->append(description->symbols_ptr, description->length());

    return repr;
}

void TaskLine::serialize_to_file(std::ofstream &file) const {
    file.write("TASK", 4);
    int32_t descr_len = description->length();

    file.write(reinterpret_cast<const char *> (&descr_len), sizeof(descr_len));
    file.write(description->symbols_ptr, descr_len);

    file.write(reinterpret_cast<const char*>(&status), sizeof(status));
}

TaskLine::TaskLine(std::ifstream &file) {
    int32_t descr_len;
    file.read(reinterpret_cast<char *> (&descr_len), sizeof(descr_len));

    char* temp = new char[descr_len];
    file.read(temp, descr_len);
    description->append(temp, descr_len);
    delete[] temp;

    file.read(reinterpret_cast<char*>(&status), sizeof(status));
    status_dispr_fill();
}

void TaskLine::status_dispr_fill() {
    char undone[] = "[   ]   ";
    undone_displ->append(undone, strlen(undone));

    char done[] = "[ * ]   ";
    done_displ->append(done, strlen(done));
}



