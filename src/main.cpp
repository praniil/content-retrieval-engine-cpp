#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include "inverted_index.hpp"
#include "document_preprocessing.hpp"

// Forward declaration
std::unordered_map<int, std::unordered_map<std::string, double>> calculate_tfidf(
    const InvertedIndex& index, int total_docs);

std::vector<std::pair<int, double>> process_query(
    const std::string& query,
    const std::unordered_map<int, std::unordered_map<std::string, double>>& tfidf_table,
    const std::vector<std::string>& documents);

void display_results(
    const std::string& query,
    const std::vector<std::pair<int, double>>& ranked_docs,
    const std::vector<std::string>& documents,
    int num_results);

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

    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "CONTENT RETRIEVAL ENGINE - SEARCH RESULTS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    // Process and display results for each query
    for (const auto& query : test_queries) {
        auto ranked_docs = process_query(query, tfidf_table, documents);
        display_results(query, ranked_docs, documents, 3);
    }

    return 0;
}
