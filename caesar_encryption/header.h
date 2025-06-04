//
// Created by Yulia Mala on 04.06.2025.
//
#ifndef HEADER_H
#define HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

    char* get_encrypted(char* raw_text, int key);
    char* get_decrypted(char* encrypted_text, int key);

#ifdef __cplusplus
}
#endif

#endif // HEADER_H

