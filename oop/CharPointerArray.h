//
// Created by Yulia Mala on 29.05.2025.
//

#ifndef CHARPOINTERARRAY_H
#define CHARPOINTERARRAY_H
#include "CharArray.h"

class CharPointerArray {
public:
    explicit CharPointerArray();
    ~CharPointerArray();

    void append(CharArray *ptr_to_char_array);
    void insert_on_index(int index, CharArray *ptr_to_char_array);
    CharArray* get(int index) const;
    void delete_ptr(int index);
    CharArray** get_subsequence(int index, int length_to_copy) const;
    int length() const;

private:
    CharArray **lines_ptr;
    static const int INITIAL_ARRAY_CAPACITY;
    int capacity = INITIAL_ARRAY_CAPACITY;
    int filled = 0;
    void alloc_more_ptrs();
};

#endif //CHARPOINTERARRAY_H
