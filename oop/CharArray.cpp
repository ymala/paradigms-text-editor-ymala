//
// Created by Yulia Mala on 29.05.2025.
//

#include "CharArray.h"
#include <cstdio>
#include <stdexcept>
#include <cstring>

const int CharArray::INITIAL_LINE_CAPACITY = 8;

CharArray::CharArray(int capacity) {
    symbols_ptr = (char *)malloc(sizeof(char) * INITIAL_LINE_CAPACITY);
}

CharArray::~CharArray() {
    free(symbols_ptr);
}
int CharArray::length() const {
    return filled;
}

void CharArray::alloc_more_symbols() {
    char *temp = (char *)realloc(symbols_ptr, sizeof(char)*capacity*2);

    if (temp != nullptr) {
        symbols_ptr = temp;
        capacity *= 2;
    }
    else {
        fprintf(stderr, "Memory allocation for symbols failed in realloc\n");
        exit(1);
    }
}

char* CharArray::get_substring(int index, int length_to_copy) const {

    if (filled < index + length_to_copy) {
        printf("You try to get substring from %d to %d, "
               "but this line has only %d symbols\n", index, index + length_to_copy, filled);
        throw std::out_of_range("Substring range is out of bounds");
    }

    char *substring = (char*)malloc((length_to_copy + 1)* sizeof(char));

    memcpy(
        substring,
        symbols_ptr + index,
        length_to_copy);

    substring[length_to_copy] = '\0';

    return substring;
}

void CharArray::insert_on_index(char *text_to_insert, int length_to_insert, int index) {

    if (index > filled) {
        printf("You try to insert on %d, "
               "but this line has only %d symbols\n", index, filled);
        return;
    }
    while (length_to_insert > capacity - index) {
        alloc_more_symbols();
    }

    int num_of_symbols_after_insertion_place = filled - index;

    char* symbols_after_insert = get_substring(
        index, num_of_symbols_after_insertion_place
        );

    memcpy(symbols_ptr + index, text_to_insert, length_to_insert);

    memcpy(
        symbols_ptr + index + length_to_insert,
        symbols_after_insert,
        num_of_symbols_after_insertion_place);

    filled += length_to_insert;
    free(symbols_after_insert);
}

void CharArray::delete_on_index(int length_to_delete, int index) {
    if (filled < index + length_to_delete) {
        printf("You try to delete from %d to %d, "
               "but this line has only %d symbols\n", index, index + length_to_delete, filled);
        throw std::out_of_range("Substring range is out of bounds");
    }
    int num_of_symbols_after_deleted = filled - (index + length_to_delete);

    char* symbols_after_deleted = get_substring(
        index + length_to_delete, num_of_symbols_after_deleted
        );

    memcpy(
    symbols_ptr + index,
    symbols_after_deleted,
    num_of_symbols_after_deleted);

    filled -= length_to_delete;
    free(symbols_after_deleted);
}


void CharArray::append(char *text_to_append, int length_to_append) {
    insert_on_index(text_to_append, length_to_append, filled);
}