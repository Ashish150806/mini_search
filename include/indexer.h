#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "tokenizer.h"

struct Document {
    int id;
    std::string text;
    int length; // Total terms in doc
    std::string filename;
};

class Indexer {
public:
    std::vector<Document> documents;
    
    // The Core Data Structure: Word -> { DocID -> Count }
    std::unordered_map<std::string, std::unordered_map<int, int>> invertedIndex;

    void addDocument(const std::string& filepath, int docId, Tokenizer& tokenizer);
    int getTotalDocuments() const;
};

#endif