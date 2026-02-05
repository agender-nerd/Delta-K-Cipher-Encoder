#include "Delta_K.hpp"

#include <iostream>
#include <string>
#include <cctype>

/**
 * @brief Performs standard monoalphabetic encryption (Unkeyed).
 * * Converts each alphabetic character in the plaintext directly to its
 * corresponding sequence of 3 glyphs from the TRIT_ALPHABET.
 * * @param plaintext The source string to encrypt.
 * @return std::string The resulting string of glyphs.
 * @note Non-alphabetic characters are preserved as-is. Spaces (' ') are converted to forward slashes.
 */
std::string encrypt(const std::string& plaintext) {
    std::string ciphertext = "";

    for (size_t i = 0; i < plaintext.length(); i++) {
        char currentChar = plaintext[i];

        if (std::isalpha(currentChar)) {
            int abcValue = abcPosition(currentChar);
            for (int j = 0; j < BASE; j++) {
                ciphertext += GLYPHS[TRIT_ALPHABET[abcValue][j]]; // add the 3 corresponding glyphs to the ciphertext
            }
        } else if (currentChar == ' ') {
            ciphertext += '/';
        } else {
            ciphertext += currentChar;
        }
    }

    return ciphertext;
}

std::string decrypt(const std::string& ciphertext) {
    std::string plaintext = "";

    
}

/**
 * @brief Performs polyalphabetic encryption using Base-3 modulo arithmetic (Keyed).
 * * This function implements the core "Delta-K" logic. For each letter of the plaintext:
 * 1. It identifies the corresponding letter in the key (cycling through the key if necessary).
 * 2. It looks up the trits for both the plaintext letter and the key letter.
 * 3. It adds the trits together modulo 3 ((plain + key) % 3).
 * 4. The resulting values determine the final glyphs.
 * * @param plaintext The source string to encrypt.
 * @param key The keyword used to scramble the encryption.
 * @return std::string The resulting string of glyphs.
 * @note This method effectively creates a unique symbol set for every letter, making
 * frequency analysis significantly more difficult.
 */
std::string encrypt(const std::string& plaintext, const std::string& key) {
    std::string ciphertext = "";
    size_t keyIndex = 0;

    for (size_t i = 0; i < plaintext.length(); i++) {
        char currentChar = plaintext[i];

        if (std::isalpha(currentChar)) {
            char currentKeyChar = key[keyIndex % key.length()];
            int keyAbcVal = abcPosition(currentKeyChar);

            int abcVal = abcPosition(currentChar);

            for (int j = 0; j < BASE; j++) {
                int keyedValue = TRIT_ALPHABET[abcVal][j] + TRIT_ALPHABET[keyAbcVal][j];
                keyedValue %= 3;
                ciphertext += GLYPHS[keyedValue]; 
            }
            
            keyIndex++; 
        } else if (currentChar == ' ') {
            ciphertext += '/';
        } else {
            ciphertext += currentChar;
        }
    }

    return ciphertext;
}

/**
 * @brief Converts a character to its 0-indexed position in the alphabet.
 * * @param abc The character to convert.
 * @return int The position (0-25) relative to 'A'.
 */
int abcPosition(char abc) {
    char abcUpper = std::toupper(abc);
    int asciiVal = abcUpper - 'A';
    return asciiVal;
}

/**
 * @brief Validates that a key is non-empty and contains only alphabetic characters.
 * * @param key The input string to validate.
 * @return true If the key is valid (not empty, only letters).
 * @return false If the key is empty or contains numbers/symbols.
 */
bool keyValidation(const std::string& key) {
    if (key.empty()) return false;

    // Iterates through every letter; if  a number or symbol is found, key is invalid
    for (size_t i = 0; i < key.length(); i++) {
        if (!std::isalpha(key[i])) {
            return false;
        }
    }

    return true;
}