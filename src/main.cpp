#include <iostream>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include "../include/tokenizer.h"
#include "../include/indexer.h"
#include "../include/search.h"
using namespace std;

namespace fs = filesystem;

int main() {
    // 1. Initialization
    Tokenizer tokenizer;
    tokenizer.loadStopwords("stopwords.txt"); // Make sure this file exists!

    Indexer indexer;
    string dataPath = "data/20_newsgroups"; // Check your path!

    cout << "Indexing documents from: " << dataPath << " ..." <<endl;
    
    // 2. Indexing Phase (with timer)
    auto start = chrono::high_resolution_clock::now();
    
    int docID = 0;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(dataPath)) {
            if (entry.is_regular_file()) {
                indexer.addDocument(entry.path().string(), docID, tokenizer);
                docID++;
                if (docID % 100 == 0) cout << "." << flush; // Progress bar
            }
        }
    } catch (const exception& e) {
        cerr << "\nError reading files: " << e.what() << endl;
        return 1;
    }

    auto end =chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    
    cout << "\nIndex complete! " << indexer.getTotalDocuments() << " documents indexed in " 
              << elapsed.count() << " seconds." << endl;

    // 3. Search Loop
    SearchEngine engine(indexer, tokenizer);
    string query;

    while (true) {
        cout << "\n-----------------------------------" << endl;
        cout << "Enter search query (or 'exit' to quit): ";
        getline(cin, query);

        if (query == "exit") break;

        auto searchStart = chrono::high_resolution_clock::now();
        vector<SearchResult> results = engine.search(query);
        auto searchEnd = chrono::high_resolution_clock::now();
        chrono::duration<double> searchTime = searchEnd - searchStart;

        cout << "Found " << results.size() << " results in " << searchTime.count() << " seconds.\n";
        
        // Show Top 5
        for (int i = 0; i < min((int)results.size(), 5); ++i) {
            int id = results[i].docId;
            cout << "[" << i+1 << "] Score: " << results[i].score 
                      << " | File: " << indexer.documents[id].filename << endl;
            
            // Print snippet (first 100 chars)
            string snippet = indexer.documents[id].text.substr(0, 100);
            replace(snippet.begin(), snippet.end(), '\n', ' '); // Remove newlines for clean display
            cout << "    Snippet: " << snippet << "..." << endl;
        }
    }

    return 0;
}