/**
 * @file cipher-encoder.cpp
 * @brief A program to encrypt text using a trinary substitution cipher.
 * Supports both a standard static alphabet and a keyword-based 
 * randomized symbol mapping.
 */

#include <iostream>
#include <string>
#include <cctype>
#include <set>

/** 
 * @brief The fixed length of the alphabet used for the cipher. 
 */
const int ALPHABET_LENGTH = 26;

/**
 * @brief The standard trinary symbol set (permutations of ▲, ▼, ◆).
 * Used as the default encoding if no key is provided.
 */
const std::string CIPHER_ALPHABET[ALPHABET_LENGTH] = 
{"▲▲▼", "▲▲◆", "▲▼▲", "▲▼▼", "▲▼◆", "▲◆▲", "▲◆▼", "▲◆◆",
"▼▲▲", "▼▲▼", "▼▲◆", "▼▼▲", "▼▼▼", "▼▼◆", "▼◆▲", "▼◆▼", "▼◆◆",
"◆▲▲", "◆▲▼", "◆▲◆", "◆▼▲", "◆▼▼", "◆▼◆", "◆◆▲", "◆◆▼", "◆◆◆"};

// Main encoder function
std::string encrypt(const std::string& plaintext, const std::string (&alphabet)[ALPHABET_LENGTH] = CIPHER_ALPHABET);

// Helper function(s)
int abcPosition(char abc);
bool keyValidation(const std::string& key);
std::string alphabetWithKey(const std::string& key);
void keyedCipherAlphabet(const std::string& keyedAlphabet, std::string (&output)[ALPHABET_LENGTH]);

/**
 * @brief Entry point of the program. 
 * Handles user input for plaintext and optional key, validates input, 
 * and outputs the resulting ciphertext.
 * * @return int Execution status code.
 */
int main() {
    std::string plaintext;
    std::string ciphertext;
    std::string key;

    std::cout << "Please enter plaintext to encode:" << std::endl;
    std::getline(std::cin, plaintext);
    
    do {
        std::cout << "Enter key (0 for normal cipher):" << std::endl;
        std::cin >> key;
        
        if (key == "0") {
            ciphertext = encrypt(plaintext);
        } else if (!keyValidation(key)) {
            std::cout << "Key invalid. Try again." << std::endl;
        } else {
            std::string keyedCipher[26];
            keyedCipherAlphabet(alphabetWithKey(key), keyedCipher);
            ciphertext = encrypt(plaintext, keyedCipher);
        }
    } while (!(keyValidation(key) || key == "0"));

    std::cout << "Encoded ciphertext:" << std::endl;
    std::cout << ciphertext << std::endl;
    return 0;
}

/**
 * @brief Encrypts a string of plaintext using the provided cipher alphabet.
 * * @param plaintext The string to be encrypted.
 * @param alphabet A reference to a string array of size 26 containing the cipher symbols.
 * Defaults to the standard CIPHER_ALPHABET if not provided.
 * @return std::string The resulting encrypted string.
 * * @note Non-alphabetic characters (numbers, punctuation, spaces) are preserved as-is.
 */
std::string encrypt(const std::string& plaintext, const std::string (&alphabet)[ALPHABET_LENGTH]) {
    std::string ciphertext = "";

    for (size_t i = 0; i < plaintext.length(); i++) {
        if (std::isalpha(plaintext[i])) {
            ciphertext += alphabet[abcPosition(plaintext[i])];
        } else {
            ciphertext += plaintext[i];
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
 * @brief Validates that a key consists only of unique alphabetic characters.
 * * @param key The input string to validate.
 * @return true If the key contains only unique letters.
 * @return false If the key contains non-letters or duplicates.
 */
bool keyValidation(const std::string& key) {
    /* Sets treat uppercase and lowercase letters as different. We're 
    using sets later in this function to verify uniqueness, so we need
    to build a string that is entirely uppercase letters to ensure the
    code works correctly */
    std::string upperKey = "";

    // Iterates through every letter; if  a number or symbol is found, key is invalid
    for (size_t i = 0; i < key.length(); i++) {
        if (!std::isalpha(key[i])) {
            return false;
        }
        upperKey += std::toupper(key[i]);
    }

    std::set<char> chars(upperKey.begin(), upperKey.end());
    return (chars.size() == upperKey.size());
}

/**
 * @brief Generates a reordered alphabet string based on a keyword.
 * The keyword is placed first, followed by the remaining unused letters
 * in alphabetical order.
 * * @param key The validated keyword.
 * @return std::string A 26-character string representing the new alphabet order.
 */
std::string alphabetWithKey(const std::string& key){
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string keyedAlphabet = "";
    for (size_t i = 0; i < key.length(); i++) {
        keyedAlphabet += std::toupper(key[i]);
    }

    for (size_t i = 0; i < keyedAlphabet.length(); i++) {
        for (size_t j = 0; j < alphabet.length(); j++) {
            if (alphabet[j] == keyedAlphabet[i]) {
                alphabet.erase(j, 1);
                break;
            }
        }
    }

    keyedAlphabet += alphabet;
    return keyedAlphabet;
}

/**
 * @brief Maps the standard trinary symbols to a keyed alphabet arrangement.
 * * This function effectively shuffles the symbols. It assigns the standard 
 * symbol for 'A' to the first letter of the keyed alphabet, the symbol for 
 * 'B' to the second letter, and so on.
 * * @param keyedAlphabet The 26-character string generated by alphabetWithKey().
 * @param output Reference to the array where the new symbol mapping will be stored.
 */
void keyedCipherAlphabet(const std::string& keyedAlphabet, std::string (&output)[ALPHABET_LENGTH]){
    for (size_t i = 0; i < ALPHABET_LENGTH; i++) {
        int index = keyedAlphabet[i] - 'A'; // For example: if i = 0 and the key is "KEY", index = 10
        output[index] = CIPHER_ALPHABET[i]; 
    }
}