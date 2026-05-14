#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include "inverted_index.hpp"
#include "document_preprocessing.hpp"

// Forward declaration for calculate_tfidf
std::unordered_map<int, std::unordered_map<std::string, double>> calculate_tfidf(
    const InvertedIndex& index, int total_docs);

// Function to process query and return ranked documents
std::vector<std::pair<int, double>> process_query(
    const std::string& query,
    const std::unordered_map<int, std::unordered_map<std::string, double>>& tfidf_table,
    const std::vector<std::string>& documents) {
    
    // Preprocess the query using the same preprocessing as documents
    std::vector<std::string> query_tokens = preprocess_text(query);
    
    // Calculate relevance score for each document
    std::unordered_map<int, double> relevance_scores;
    
    for (int doc_id = 0; doc_id < documents.size(); doc_id++) {
        double score = 0.0;
        
        // Sum TF-IDF scores for matching terms
        for (const auto& term : query_tokens) {
            if (tfidf_table.count(doc_id)) {
                const auto& doc_tfidf = tfidf_table.at(doc_id);
                if (doc_tfidf.count(term)) {
                    score += doc_tfidf.at(term);
                }
            }
        }
        
        relevance_scores[doc_id] = score;
    }
    
    // Sort documents by relevance score (descending)
    std::vector<std::pair<int, double>> ranked_docs;
    for (const auto& [doc_id, score] : relevance_scores) {
        if (score > 0.0) {  // Only include documents with non-zero scores
            ranked_docs.push_back({doc_id, score});
        }
    }
    
    std::sort(ranked_docs.begin(), ranked_docs.end(), 
        [](const auto& a, const auto& b) {
            return a.second > b.second;  // Sort by score descending
        });
    
    return ranked_docs;
}

// Function to display query results
void display_results(
    const std::string& query,
    const std::vector<std::pair<int, double>>& ranked_docs,
    const std::vector<std::string>& documents,
    int num_results = 5) {
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "Query: \"" << query << "\"" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (ranked_docs.empty()) {
        std::cout << "No matching documents found." << std::endl;
        return;
    }
    
    int results_to_show = std::min(num_results, (int)ranked_docs.size());
    
    std::cout << "Top " << results_to_show << " Results:" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (int i = 0; i < results_to_show; i++) {
        int doc_id = ranked_docs[i].first;
        double score = ranked_docs[i].second;
        
        std::cout << "\n[" << (i + 1) << "] Document " << doc_id 
                  << " (Relevance Score: " << std::fixed << std::setprecision(4) 
                  << score << ")" << std::endl;
        std::cout << "Content: " << documents[doc_id] << std::endl;
    }
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
}

#ifndef BUILD_AS_LIB
int main() {
    std::vector<std::string> documents = {
        "Machine learning is a subset of artificial intelligence focused on developing algorithms that learn from data.",
        "Artificial intelligence involves creating systems that can perform tasks requiring human intelligence.",
        "Deep learning is a type of machine learning based on artificial neural networks with multiple layers.",
        "Natural language processing allows computers to understand and generate human language.",
        "Computer vision enables machines to interpret and understand the visual world.",
        "Reinforcement learning is an area of machine learning concerned with how agents take actions in an environment.",
        "Supervised learning algorithms learn from labeled training data to make predictions on new data.",
        "Unsupervised learning deals with unlabeled data, finding patterns and structures within it.",
        "A neural network is a computational model inspired by the human brain's structure and function.",
        "Big data refers to large and complex data sets that require advanced processing techniques."
    };

    std::cout << "Building inverted index..." << std::endl;
    InvertedIndex index = build_inverted_index(documents);

    std::cout << "Calculating TF-IDF values..." << std::endl;
    auto tfidf_table = calculate_tfidf(index, documents.size());

    // Test queries
    std::vector<std::string> test_queries = {
        "machine learning algorithms",
        "artificial intelligence systems",
        "neural networks and deep learning",
        "natural language processing",
        "computer vision images"
    };

    // Process and display results for each query
    for (const auto& query : test_queries) {
        auto ranked_docs = process_query(query, tfidf_table, documents);
        display_results(query, ranked_docs, documents, 3);
    }

    return 0;
}
#endif
