#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <secure/_string.h>
//
// Created by Yulia Mala on 04.06.2025.
//
int get_key_from_user() {
    int ch;
    int key = 0;
    printf("Enter key: ");
    if (scanf("%d", &key) != 1) {
        printf("Invalid input. One integer expected\n");
    }
    while ((ch = getchar()) != '\n' && ch != EOF);
    return key;
}

char* get_text_from_user() {
    char buff[1000];
    printf("Type a text: ");
    fgets(buff, sizeof(buff), stdin);

    size_t line_length = strlen(buff);
    if (line_length > 0 && buff[line_length - 1] == '\n') {
        buff[line_length - 1] = '\0';
        line_length--;
    }
    char* result = (char*)malloc(line_length + 1);

    memcpy(result, buff, line_length);
    result[line_length] = '\0';

    return result;
}