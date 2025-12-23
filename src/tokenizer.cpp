#include "../include/tokenizer.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

void Tokenizer::loadStopwords(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string word;
    while (file >> word) {
        stopwords.insert(word);
    }
}

// Remove punctuation and convert to lowercase
std::string Tokenizer::cleanToken(std::string rawToken) {
    std::string clean = "";
    for (char c : rawToken) {
        if (std::isalnum(c)) {
            clean += std::tolower(c);
        }
    }
    return clean;
}

std::vector<std::string> Tokenizer::tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string word;

    while (ss >> word) {
        std::string cleaned = cleanToken(word);
        // Only add if not empty and not a stopword
        if (!cleaned.empty() && stopwords.find(cleaned) == stopwords.end()) {
            tokens.push_back(cleaned);
        }
    }
    return tokens;
}