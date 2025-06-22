//
// Created by Yulia Mala on 29.05.2025.
//

#ifndef CHARARRAY_H
#define CHARARRAY_H

class CharArray {
public:
    explicit CharArray(int capacity=INITIAL_LINE_CAPACITY);
    ~CharArray();

    char *symbols_ptr;
    void insert_on_index(char *text_to_insert, int length_to_insert, int index);
    void append(char *text_to_append, int length_to_append);
    char* get_substring(int index, int length_to_copy) const;
    void delete_on_index(int length_to_delete, int index);
    int length() const;
    void append_null_term_str(char *text_to_append);
    void clear();


private:
    static const int INITIAL_LINE_CAPACITY;
    int capacity = INITIAL_LINE_CAPACITY;
    int filled = 0;
    void alloc_more_symbols();
};



#endif //CHARARRAY_H
