#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <set>

class Tokenizer {
public:
    std::set<std::string> stopwords;

    void loadStopwords(const std::string& filepath);
    std::string cleanToken(std::string rawToken);
    std::vector<std::string> tokenize(const std::string& text);
};

#endif