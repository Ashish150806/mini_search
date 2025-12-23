#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include "indexer.h"
#include "tokenizer.h"

struct SearchResult {
    int docId;
    double score;
};

class SearchEngine {
private:
    Indexer& indexer;
    Tokenizer& tokenizer;

public:
    SearchEngine(Indexer& idx, Tokenizer& tok);
    std::vector<SearchResult> search(const std::string& query);
};

#endif