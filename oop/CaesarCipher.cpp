//
// Created by Yulia Mala on 22.06.2025.
//

#include "CaesarCipher.h"

#include <cstdio>
#include <dlfcn.h>

CaesarCipher::CaesarCipher() {
    handle = dlopen(library_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading lib: %s\n", dlerror());
        dlclose(handle);
    }

    get_encrypted = (encrypt_func)dlsym(handle, "get_encrypted");
    get_decrypted = (decrypt_func)dlsym(handle, "get_decrypted");

    if (!get_encrypted || !get_decrypted) {
        fprintf(stderr, "Error loading func: %s\n", dlerror());
        dlclose(handle);
    }
}

CaesarCipher::~CaesarCipher() {
    if (handle) {
        dlclose(handle);
    }
}

char* CaesarCipher::encrypt(char* text, int key) {
    if (!handle || !get_encrypted) return nullptr;
    return get_encrypted(text, key);
}

char* CaesarCipher::decrypt(char* text, int key) {
    if (!handle || !get_decrypted) return nullptr;
    return get_decrypted(text, key);
}
