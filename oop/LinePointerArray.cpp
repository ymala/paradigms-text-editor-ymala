//
// Created by Yulia Mala on 29.05.2025.
//

#include "LinePointerArray.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

const int LinePointerArray::INITIAL_ARRAY_CAPACITY = 8;

LinePointerArray::LinePointerArray() {
    lines_ptr = (Line **)malloc(sizeof(Line *) * INITIAL_ARRAY_CAPACITY);
}

LinePointerArray::~LinePointerArray() {
    for (int i=0; i< filled; i++) {
        delete lines_ptr[i];
    }
    free(lines_ptr);
}

void LinePointerArray::alloc_more_ptrs() {
    Line **temp = (Line **)realloc(lines_ptr, sizeof(Line *)*capacity*2);

    if (temp != nullptr) {
        lines_ptr = temp;
        capacity *= 2;
    }
    else {
        fprintf(stderr, "Memory allocation for symbols failed in realloc\n");
        exit(1);
    }
}

void LinePointerArray::insert_on_index(int index, Line *ptr_to_line) {
    if (index > filled) {
        printf("You try to insert on position %d with 0-based index "
               "but there are only %d lines\n", index, filled);
        throw std::out_of_range("Index is out of bounds");
    }
    if (capacity - filled < 1) {
        alloc_more_ptrs();
    }

    int num_of_ptrs_after_insert = filled - index;
    memmove(
    lines_ptr + index + 1,
    lines_ptr + index,
    sizeof(Line*) * num_of_ptrs_after_insert
    );

    lines_ptr[index] = ptr_to_line;
    filled++;
}

void LinePointerArray::append(Line *ptr_to_line) {
    if (capacity - filled < 1) {
        alloc_more_ptrs();
    }
    lines_ptr[filled] = ptr_to_line;
    filled++;
}

Line* LinePointerArray::get(int index) const {
    if (index >= filled) {
        printf("You try to get line with 0-based index %d "
               "but there are only %d lines\n", index, filled);
        throw std::out_of_range("Index is out of bounds");
    }
    return lines_ptr[index];
}

int LinePointerArray::length() const {
    return filled;
}

void LinePointerArray::extract_ptr(int index) {
    if (index >= filled) {
        printf("You try to delete line with 0-based index %d "
               "but there are only %d lines\n", index, filled);
        throw std::out_of_range("Index is out of bounds");
    }

    int num_of_ptrs_after_deleted = filled - (index + 1);

    memmove(
        lines_ptr + index,
        lines_ptr + index + 1,
        sizeof(Line*) * num_of_ptrs_after_deleted
        );
    filled--;
}



Line **LinePointerArray::get_subsequence(int index, int length_to_copy) const {
    if (filled < index + length_to_copy) {
        printf("You try to get subsequence from %d to %d, "
               "but this array has only %d pointers\n", index, index + length_to_copy, filled);
        throw std::out_of_range("Range is out of bounds");
    }

    Line **subsequence = (Line **)malloc((length_to_copy)* sizeof(Line *));

    memcpy(
        subsequence,
        lines_ptr + index,
        length_to_copy * sizeof(Line*));

    return subsequence;
}

