//
// Created by Yulia Mala on 29.05.2025.
//

#ifndef LINEPOINTERARRAY_H
#define LINEPOINTERARRAY_H
#include "Line.h"

class LinePointerArray {
public:
    explicit LinePointerArray();
    ~LinePointerArray();

    void append(Line *ptr_to_line);
    void insert_on_index(int index, Line *ptr_to_line);
    Line* get(int index) const;
    void delete_ptr(int index);
    Line** get_subsequence(int index, int length_to_copy) const;
    int length() const;

private:
    Line **lines_ptr;
    static const int INITIAL_ARRAY_CAPACITY;
    int capacity = INITIAL_ARRAY_CAPACITY;
    int filled = 0;
    void alloc_more_ptrs();
};

#endif //LINEPOINTERARRAY_H
