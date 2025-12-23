#include "../include/search.h"
#include <cmath> // for log()
#include <algorithm> // for sort
#include <iostream>

SearchEngine::SearchEngine(Indexer& idx, Tokenizer& tok) 
    : indexer(idx), tokenizer(tok) {}

std::vector<SearchResult> SearchEngine::search(const std::string& query) {
    std::vector<std::string> queryTokens = tokenizer.tokenize(query);
    std::unordered_map<int, double> docScores; // DocID -> Score accumulator

    int totalDocs = indexer.getTotalDocuments();

    // Loop through every word in the user's query
    for (const std::string& term : queryTokens) {
        
        // Check if term exists in our index
        if (indexer.invertedIndex.find(term) == indexer.invertedIndex.end()) {
            continue; // Skip words not in dataset
        }

        // Calculate IDF for this term (Constant across all docs)
        int docsWithTerm = indexer.invertedIndex[term].size();
        double idf = std::log10((double)totalDocs / (docsWithTerm + 1)); // Manual IDF logic

        // Look at every document containing this term
        for (auto const& [docID, count] : indexer.invertedIndex[term]) {
            
            // Calculate TF for this document
            // Formula: (Frequency of term in doc) / (Total terms in doc)
            int docLength = indexer.documents[docID].length;
            double tf = (double)count / docLength;

            // TF-IDF Score
            double tfidf = tf * idf;

            // Add to document's total score
            docScores[docID] += tfidf;
        }
    }

    // Convert map to vector for sorting
    std::vector<SearchResult> results;
    for (auto const& [id, score] : docScores) {
        results.push_back({id, score});
    }

    // Sort by score (Highest first)
    std::sort(results.begin(), results.end(), [](const SearchResult& a, const SearchResult& b) {
        return a.score > b.score;
    });

    return results;
}