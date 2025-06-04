#include <cctype>
#include <stdexcept>

extern "C" {

    __attribute__((visibility("default")))
char* get_encrypted(char* raw_text, int key) {
    int text_length = 0;
    while (raw_text[text_length] != '\0') {
        text_length++;
    }
    char *encrypted_text = (char*)malloc(text_length + 1);

    int i = 0;
    for (i = 0; i < text_length; i++) {
        if (std::isalpha(raw_text[i])) {
            int base = 65;
            if (std::islower(raw_text[i])) {
                base = 97;
            }
            int index = raw_text[i];
            encrypted_text[i] = static_cast<char>(
                (index - base + key) % 26 + base
                );
        }
        else {
            encrypted_text[i] = raw_text[i];
        }
    }
    encrypted_text[text_length] = '\0';
    return encrypted_text;
}


    __attribute__((visibility("default")))
char* get_decrypted(char* encrypted_text, int key) {
    int text_length = 0;
    while (encrypted_text[text_length] != '\0') {
        text_length++;
    }
    char *decrypted_text = (char*)malloc(text_length + 1);

    int i = 0;
    for (i = 0; i < text_length; i++) {
        if (std::isalpha(encrypted_text[i])) {
            int base = 65;
            if (std::islower(encrypted_text[i])) {
                base = 97;
            }
            int index = encrypted_text[i];
            decrypted_text[i] = static_cast<char>(
                (index - base - key + 26) % 26 + base
                );
        }
        else {
            decrypted_text[i] = encrypted_text[i];
        }
    }
    decrypted_text[text_length] = '\0';
    return decrypted_text;
}

    }