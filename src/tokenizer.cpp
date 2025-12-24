#include "../include/tokenizer.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

void Tokenizer::loadStopwords(const string& filepath) {
    ifstream file(filepath);
    string word;
    while (file >> word) {
        stopwords.insert(word);
    }
}

// Remove punctuation and convert to lowercase
string Tokenizer::cleanToken(string rawToken) {
    string clean = "";
    for (char c : rawToken) {
        if (isalnum(c)) {
            clean += tolower(c);
        }
    }
    return clean;
}

vector<string> Tokenizer::tokenize(const string& text) {
    vector<string> tokens;
    stringstream ss(text);
    string word;

    while (ss >> word) {
        string cleaned = cleanToken(word);
        // Only add if not empty and not a stopword
        if (!cleaned.empty() && stopwords.find(cleaned) == stopwords.end()) {
            tokens.push_back(cleaned);
        }
    }
    return tokens;
}