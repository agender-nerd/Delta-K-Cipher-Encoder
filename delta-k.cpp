#include <iostream>
#include <string>
#include <cctype>

const int ALPHABET_LENGTH = 26;
const int BASE = 3;

const std::string GLYPHS[BASE] = {"▲", "▼", "◆"};

const int TRIT_ALPHABET[ALPHABET_LENGTH][BASE] = {
    {0, 0, 1}, {0, 0, 2}, {0, 1, 0}, {0, 1, 1}, {0, 1, 2}, 
    {0, 2, 0}, {0, 2, 1}, {0, 2, 2}, {1, 0, 0}, {1, 0, 1}, 
    {1, 0, 2}, {1, 1, 0}, {1, 1, 1}, {1, 1, 2}, {1, 2, 0}, 
    {1, 2, 1}, {1, 2, 2}, {2, 0, 0}, {2, 0, 1}, {2, 0, 2},
    {2, 1, 0}, {2, 1, 1}, {2, 1, 2}, {2, 2, 0}, {2, 2, 1}, 
    {2, 2, 2}
};

// Main encoder function
std::string encrypt(const std::string& plaintext);
std::string encrypt(const std::string& plaintext, const std::string& key);

// Helper function(s)
int abcPosition(char abc);
bool keyValidation(const std::string& key);

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
            ciphertext = encrypt(plaintext, key);
        }
    } while (!(keyValidation(key) || key == "0"));

    std::cout << "Encoded ciphertext:" << std::endl;
    std::cout << ciphertext << std::endl;
    return 0;
}

std::string encrypt(const std::string& plaintext) {
    std::string ciphertext = "";

    for (size_t i = 0; i < plaintext.length(); i++) {
        char currentChar = plaintext[i];

        if (std::isalpha(currentChar)) {
            int abcValue = abcPosition(currentChar);
            for (int j = 0; j < BASE; j++) {
                ciphertext += GLYPHS[TRIT_ALPHABET[abcValue][j]]; // add the 3 corresponding glyphs to the ciphertext
            }
        } else {
            ciphertext += currentChar;
        }
    }

    return ciphertext;
}

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
        } else {
            ciphertext += currentChar;
        }
    }

    return ciphertext;
}

int abcPosition(char abc) {
    char abcUpper = std::toupper(abc);
    int asciiVal = abcUpper - 'A';
    return asciiVal;
}

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