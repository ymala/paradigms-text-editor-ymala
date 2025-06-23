//
// Created by Yulia Mala on 22.06.2025.
//

#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H



class CaesarCipher {
public:
    CaesarCipher();
    ~CaesarCipher();
    char* encrypt(char* text, int key);
    char* decrypt(char* text, int key);
private:
    void* handle = nullptr;
    const char* library_path = "../libcaesar.dylib";

    typedef char* (*encrypt_func)(char*, int);
    typedef char* (*decrypt_func)(char*, int);
    encrypt_func get_encrypted;
    decrypt_func get_decrypted;
};



#endif //CAESARCIPHER_H
