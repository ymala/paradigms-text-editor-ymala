//
// Created by Yulia Mala on 20.06.2025.
//

#include "ContactLine.h"

#include <fstream>

ContactLine::ContactLine(char *in_name, char *in_email) {
    name->append_null_term_str(in_name);
    email->append_null_term_str(in_email);
}

CharArray *ContactLine::str_repr_ptr() {
    char c_buffer[] = "Contact: ";
    char e_buffer[] = "  Email: ";

    repr->clear();

    repr->append_null_term_str(c_buffer);
    repr->append_null_term_str(name->symbols_ptr);
    repr->append_null_term_str(e_buffer);
    repr->append_null_term_str(email->symbols_ptr);
    return repr;
}

void ContactLine::serialize_to_file(std::ofstream &file) const {
    file.write("CONT", 4);
    int32_t name_len = name->length();
    int32_t email_len = email->length();

    file.write(reinterpret_cast<const char *> (&name_len), sizeof(name_len));
    file.write(name->symbols_ptr, name_len);

    file.write(reinterpret_cast<const char *> (&email_len), sizeof(email_len));
    file.write(email->symbols_ptr, email_len);
}

ContactLine::ContactLine(std::ifstream &file) {
    int32_t name_len;
    file.read(reinterpret_cast<char *> (&name_len), sizeof(name_len));
    char* temp_name = new char[name_len];
    file.read(temp_name, name_len);
    name->append(temp_name, name_len);
    delete[] temp_name;

    int32_t email_len;
    file.read(reinterpret_cast<char *> (&email_len), sizeof(email_len));
    char* temp_email = new char[email_len];
    file.read(temp_email, email_len);
    email->append(temp_email, email_len);
    delete[] temp_email;
}


std::vector<CharArray*> ContactLine::get_text_fields() {
    std::vector<CharArray*> fields;
    fields.push_back(name);
    fields.push_back(email);
    return fields;
}
