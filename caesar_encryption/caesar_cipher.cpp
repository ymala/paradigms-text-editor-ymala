#include <stdexcept>
#include <vector>

extern "C" {

    const int ALPHABET_SIZE = 26;
    const int UPPERCASE_BASE = 65;
    const int LOWERCASE_BASE = 97;

    char* process_text(const char* text, int key, bool encrypt) {
        if (!text) return nullptr;

        size_t length = strlen(text);
        char* result = static_cast<char*>(malloc(length + 1));
        if (!result) return nullptr;

        for (size_t i = 0; i < length; i++) {
            if (std::isalpha(text[i])) {
                int base = std::isupper(text[i]) ? UPPERCASE_BASE : LOWERCASE_BASE;
                int shift = encrypt ? key : -key;

                int shifted = (text[i] - base + shift + ALPHABET_SIZE) % ALPHABET_SIZE;
                result[i] = static_cast<char>(shifted + base);
            } else {
                result[i] = text[i];
            }
        }
        result[length] = '\0';
        return result;
    }

    __attribute__((visibility("default")))
    char* get_encrypted(char* raw_text, int key) {
        return process_text(raw_text, key, true);
    }

    __attribute__((visibility("default")))
    char* get_decrypted(char* encrypted_text, int key) {
        return process_text(encrypted_text, key, false);
    }
}
