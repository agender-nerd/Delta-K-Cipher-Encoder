#ifndef DELTA_K_HPP
#define DELTA_K_HPP

#include <string>

/**
 * @brief The length of the standard alphabet (A-Z).
 */
const int ALPHABET_LENGTH = 26;

/**
 * @brief The base of the numbering system used for encryption (Base-3).
 */
const int BASE = 3;

/**
 * @brief The glyphs representing the three digits of the trinary system.
 * Index 0 = ▲, Index 1 = ▼, Index 2 = ◆.
 */
const std::string GLYPHS[BASE] = {"▲", "▼", "◆"};

/**
 * @brief A 2D array mapping each letter (0-25) to its unique 3-trit representation.
 * Each row corresponds to a letter, and the columns contain
 * the three trits (0, 1, or 2) that represent that letter.
 */
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

// Main decoder function
std::string decrypt(const std::string& ciphertext);

// Helper function(s)
int abcPosition(char abc);
bool keyValidation(const std::string& key);
bool isGlyph(char c);
int glyphVal(char c);
int abcSearch(int a, int b, int c);

#endif