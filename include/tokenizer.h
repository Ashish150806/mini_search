#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <set>
using namespace std;

class Tokenizer {
public:
    set<string> stopwords;

    void loadStopwords(const string& filepath);
    string cleanToken(string rawToken);
    vector<string> tokenize(const string& text);
};

#endif