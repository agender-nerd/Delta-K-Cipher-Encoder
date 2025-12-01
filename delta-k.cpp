#include <iostream>
#include <string>
#include <cctype>
#include <set>

const int ALPHABET_LENGTH = 26;

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

int abcPosition(char abc) {
    char abcUpper = std::toupper(abc);
    int asciiVal = abcUpper - 'A';
    return asciiVal;
}

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

void keyedCipherAlphabet(const std::string& keyedAlphabet, std::string (&output)[ALPHABET_LENGTH]){
    for (size_t i = 0; i < ALPHABET_LENGTH; i++) {
        int index = keyedAlphabet[i] - 'A'; // For example: if i = 0 and the key is "KEY", index = 10
        output[index] = CIPHER_ALPHABET[i]; 
    }
}