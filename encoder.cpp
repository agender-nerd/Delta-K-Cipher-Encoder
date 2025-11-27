#include <iostream>
#include <string>
#include <cctype>

const std::string CIPHER_ALPHABET[26] = 
{"▲▲▼", "▲▲◆", "▲▼▲", "▲▼▼", "▲▼◆", "▲◆▲", "▲◆▼", "▲◆◆",
"▼▲▲", "▼▲▼", "▼▲◆", "▼▼▲", "▼▼▼", "▼▼◆", "▼◆▲", "▼◆▼", "▼◆◆",
"◆▲▲", "◆▲▼", "◆▲◆", "◆▼▲", "◆▼▼", "◆▼◆", "◆◆▲", "◆◆▼", "◆◆◆"};

// Main encoder function
std::string encrypt(const std::string& plaintext);

// Helper function(s)
int abcPosition(char abc);

int main() {
    std::string plaintext;

    std::cout << "Please enter plaintext to encode:" << std::endl;
    std::getline(std::cin, plaintext);

    std::string ciphertext = encrypt(plaintext);

    std::cout << "Encoded ciphertext:" << std::endl;
    std::cout << ciphertext << std::endl;
    return 0;
}

std::string encrypt(const std::string& plaintext) {
    std::string ciphertext = "";
    int charPosition;

    for (int i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] == ' ') {
            ciphertext += "   ";
        } else {
            charPosition = abcPosition(plaintext[i]);
        }

        if (charPosition >= 0 && charPosition <= 25) {
            ciphertext += CIPHER_ALPHABET[charPosition];
        } else {
            ciphertext += plaintext[i];
        }
    }

    return ciphertext;
}

int abcPosition(char abc) {
    char abcUpper = std::toupper(abc);
    int asciiVal = abcUpper - 65;
    return asciiVal;
}