//
// Created by Yulia Mala on 29.05.2025.
//

#include "CharPointerArray.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

const int CharPointerArray::INITIAL_ARRAY_CAPACITY = 8;

CharPointerArray::CharPointerArray() {
    lines_ptr = (CharArray **)malloc(sizeof(CharArray *) * INITIAL_ARRAY_CAPACITY);
}

CharPointerArray::~CharPointerArray() {
    for (int i=0; i< filled; i++) {
        delete lines_ptr[i];
    }
    free(lines_ptr);
}

void CharPointerArray::alloc_more_ptrs() {
    CharArray **temp = (CharArray **)realloc(lines_ptr, sizeof(CharArray *)*capacity*2);

    if (temp != nullptr) {
        lines_ptr = temp;
        capacity *= 2;
    }
    else {
        fprintf(stderr, "Memory allocation for symbols failed in realloc\n");
        exit(1);
    }
}

void CharPointerArray::insert_on_index(int index, CharArray *ptr_to_char_array) {
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
    sizeof(CharArray*) * num_of_ptrs_after_insert
    );

    lines_ptr[index] = ptr_to_char_array;
    filled++;
}

void CharPointerArray::append(CharArray *ptr_to_char_array) {
    if (capacity - filled < 1) {
        alloc_more_ptrs();
    }
    lines_ptr[filled] = ptr_to_char_array;
    filled++;
}

CharArray* CharPointerArray::get(int index) const {
    if (index >= filled) {
        printf("You try to get line with 0-based index %d "
               "but there are only %d lines\n", index, filled);
        throw std::out_of_range("Index is out of bounds");
    }
    return lines_ptr[index];
}

int CharPointerArray::length() const {
    return filled;
}

void CharPointerArray::delete_ptr(int index) {
    if (index >= filled) {
        printf("You try to delete line with 0-based index %d "
               "but there are only %d lines\n", index, filled);
        throw std::out_of_range("Index is out of bounds");
    }

    delete lines_ptr[index];
    int num_of_ptrs_after_deleted = filled - (index + 1);

    memmove(
        lines_ptr + index,
        lines_ptr + index + 1,
        sizeof(CharArray*) * num_of_ptrs_after_deleted
        );
    filled--;
}

CharArray **CharPointerArray::get_subsequence(int index, int length_to_copy) const {
    if (filled < index + length_to_copy) {
        printf("You try to get subsequence from %d to %d, "
               "but this array has only %d pointers\n", index, index + length_to_copy, filled);
        throw std::out_of_range("Range is out of bounds");
    }

    CharArray **subsequence = (CharArray **)malloc((length_to_copy)* sizeof(CharArray *));

    memcpy(
        subsequence,
        lines_ptr + index,
        length_to_copy * sizeof(CharArray*));

    return subsequence;
}

