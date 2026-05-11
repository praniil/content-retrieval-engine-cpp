#include "inverted_index.hpp"
#include "document_preprocessing.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include <algorithm>

std::unordered_map<int, std::unordered_map<std::string, double>> calculate_tfidf(const InvertedIndex& index, int total_docs) {
    std::unordered_map<int, std::unordered_map<std::string, double>> tfidf_table;
    std::unordered_map<int, int> doc_lengths;
    //calculate total terms for each document 
    for (const auto& [term, postings]: index){
        for(const auto& entry:postings){
            int doc_id = entry.first;
            int term_count = entry.second.size();
            doc_lengths[doc_id] += term_count;
        }
    }

    // calculate tf-idf
    for (const auto& [term, postings]: index) {
        int n_t = postings.size(); //number of documents containing the terms
        double idf = std::log(static_cast<double>(total_docs) / n_t);

        for (const auto& entry: postings) {
            int doc_id = entry.first;
            int term_count = entry.second.size();
            double tf = static_cast<double>(term_count) / doc_lengths[doc_id];

            tfidf_table[doc_id][term] = tf*idf;
        }
                                
    }
    return tfidf_table;
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

    // Display some results
    std::cout << "\nTF-IDF Sample Results (Top 5 terms for Doc 0):" << std::endl;
    int doc_id = 0;
    if (tfidf_table.count(doc_id)) {
        // Sort terms by TF-IDF score for display
        std::vector<std::pair<std::string, double>> sorted_terms(tfidf_table[doc_id].begin(), tfidf_table[doc_id].end());
        std::sort(sorted_terms.begin(), sorted_terms.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        std::cout << std::left << std::setw(15) << "Term" << "Score" << std::endl;
        std::cout << "---------------------------" << std::endl;
        for (int i = 0; i < std::min(5, (int)sorted_terms.size()); ++i) {
            std::cout << std::left << std::setw(15) << sorted_terms[i].first << std::fixed << std::setprecision(4) << sorted_terms[i].second << std::endl;
        }
    }

    std::cout << "\nTF-IDF Sample Results (Top 5 terms for Doc 3):" << std::endl;
    doc_id = 3;
    if (tfidf_table.count(doc_id)) {
        std::vector<std::pair<std::string, double>> sorted_terms(tfidf_table[doc_id].begin(), tfidf_table[doc_id].end());
        std::sort(sorted_terms.begin(), sorted_terms.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        std::cout << std::left << std::setw(15) << "Term" << "Score" << std::endl;
        std::cout << "---------------------------" << std::endl;
        for (int i = 0; i < std::min(5, (int)sorted_terms.size()); ++i) {
            std::cout << std::left << std::setw(15) << sorted_terms[i].first << std::fixed << std::setprecision(4) << sorted_terms[i].second << std::endl;
        }
    }

    return 0;
}
#endif

