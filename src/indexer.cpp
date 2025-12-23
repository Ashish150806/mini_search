#include "../include/indexer.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Helper to read file
string readFile(const std::string& path) {
    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Indexer::addDocument(const std::string& filepath, int docId, Tokenizer& tokenizer) {
    string content = readFile(filepath);
    vector<string> tokens = tokenizer.tokenize(content);

    // Create Document object
    Document doc;
    doc.id = docId;
    doc.text = content;
    doc.length = tokens.size();
    doc.filename = filepath; // Optional: store filename
    documents.push_back(doc);

    // BUILD INVERTED INDEX
    for (const string& word : tokens) {
        // Increment frequency of 'word' in 'docId'
        invertedIndex[word][docId]++;
    }
}

int Indexer::getTotalDocuments() const {
    return documents.size();
}