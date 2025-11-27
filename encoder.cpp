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

    for (size_t i = 0; i < plaintext.length(); i++) {
        if (std::isalpha(plaintext[i])) {
            ciphertext += CIPHER_ALPHABET[abcPosition(plaintext[i])];
        } else {
            ciphertext += plaintext[i];
        }
    }

    return ciphertext;
}

int abcPosition(char abc) {
    char abcUpper = std::toupper(abc);
    int asciiVal = abcUpper - 'A';
    return asciiVal;
}