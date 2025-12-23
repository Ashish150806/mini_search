#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "tokenizer.h"
using namespace std;

struct Document {
    int id;
    string text;
    int length; // Total terms in doc
    string filename;
};

class Indexer {
public:
    vector<Document> documents;
    
    // The Core Data Structure: Word -> { DocID -> Count }
    unordered_map<string,unordered_map<int, int>> invertedIndex;

    void addDocument(const string& filepath, int docId, Tokenizer& tokenizer);
    int getTotalDocuments() const;
};

#endif