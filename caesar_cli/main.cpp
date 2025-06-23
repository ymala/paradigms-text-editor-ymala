#include <cstdio>
#include <dlfcn.h>
#include "header.h"

//
// Created by Yulia Mala on 04.06.2025.
//


int main() {
    void* handle = dlopen("../libcaesar.dylib", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    typedef char* (*encrypt_func)(char*, int);
    typedef char* (*decrypt_func)(char*, int);

    encrypt_func get_encrypted = (encrypt_func)dlsym(handle, "get_encrypted");
    if (!get_encrypted) {
        fprintf(stderr, "Error loading encrypt: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    decrypt_func get_decrypted = (decrypt_func)dlsym(handle, "get_decrypted");
    if (!get_decrypted) {
        fprintf(stderr, "Error loading decrypt: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }


    printf("You could encrypt now... ");
    char* text_to_encrypt = get_text_from_user();
    int key_to_encrypt = get_key_from_user();
    char* encrypted_text = get_encrypted(text_to_encrypt, key_to_encrypt);
    printf(encrypted_text);

    printf("\nYou could decrypt now... ");
    char* text_to_decrypt = get_text_from_user();
    int key_to_decrypt = get_key_from_user();
    char* decrypted_text = get_decrypted(text_to_decrypt, key_to_decrypt);
    printf(decrypted_text);

    dlclose(handle);

    return 0;
}