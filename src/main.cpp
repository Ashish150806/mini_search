#include <iostream>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include "../include/tokenizer.h"
#include "../include/indexer.h"
#include "../include/search.h"

namespace fs = std::filesystem;

int main() {
    // 1. Initialization
    Tokenizer tokenizer;
    tokenizer.loadStopwords("stopwords.txt"); // Make sure this file exists!

    Indexer indexer;
    std::string dataPath = "data/20_newsgroups"; // Check your path!

    std::cout << "Indexing documents from: " << dataPath << " ..." << std::endl;
    
    // 2. Indexing Phase (with timer)
    auto start = std::chrono::high_resolution_clock::now();
    
    int docID = 0;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(dataPath)) {
            if (entry.is_regular_file()) {
                indexer.addDocument(entry.path().string(), docID, tokenizer);
                docID++;
                if (docID % 100 == 0) std::cout << "." << std::flush; // Progress bar
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "\nError reading files: " << e.what() << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    
    std::cout << "\nIndex complete! " << indexer.getTotalDocuments() << " documents indexed in " 
              << elapsed.count() << " seconds." << std::endl;

    // 3. Search Loop
    SearchEngine engine(indexer, tokenizer);
    std::string query;

    while (true) {
        std::cout << "\n-----------------------------------" << std::endl;
        std::cout << "Enter search query (or 'exit' to quit): ";
        std::getline(std::cin, query);

        if (query == "exit") break;

        auto searchStart = std::chrono::high_resolution_clock::now();
        std::vector<SearchResult> results = engine.search(query);
        auto searchEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> searchTime = searchEnd - searchStart;

        std::cout << "Found " << results.size() << " results in " << searchTime.count() << " seconds.\n";
        
        // Show Top 5
        for (int i = 0; i < std::min((int)results.size(), 5); ++i) {
            int id = results[i].docId;
            std::cout << "[" << i+1 << "] Score: " << results[i].score 
                      << " | File: " << indexer.documents[id].filename << std::endl;
            
            // Print snippet (first 100 chars)
            std::string snippet = indexer.documents[id].text.substr(0, 100);
            std::replace(snippet.begin(), snippet.end(), '\n', ' '); // Remove newlines for clean display
            std::cout << "    Snippet: " << snippet << "..." << std::endl;
        }
    }

    return 0;
}