#include "../include/indexer.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Helper to read file
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Indexer::addDocument(const std::string& filepath, int docId, Tokenizer& tokenizer) {
    std::string content = readFile(filepath);
    std::vector<std::string> tokens = tokenizer.tokenize(content);

    // Create Document object
    Document doc;
    doc.id = docId;
    doc.text = content;
    doc.length = tokens.size();
    doc.filename = filepath; // Optional: store filename
    documents.push_back(doc);

    // BUILD INVERTED INDEX
    for (const std::string& word : tokens) {
        // Increment frequency of 'word' in 'docId'
        invertedIndex[word][docId]++;
    }
}

int Indexer::getTotalDocuments() const {
    return documents.size();
}