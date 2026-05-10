#include<iostream>
#include<vector>
#include<string>
#include <unordered_map>
#include"document_preprocessing.hpp"
#include <fstream>

std::unordered_map<std::string, std::vector<std::pair<int, std::vector<int>>>> build_inverted_index(std::vector<std::string>& documents) {
    // build inverted index 
    // store the index in csv file
    std::vector<std::vector<std::string>> all_tokens;
    std::unordered_map<std::string, std::vector<std::pair<int, std::vector<int>>>> index_dictionary;
    for(int i = 0; i < documents.size(); i++) {
        std::vector<std::string>tokens;
        tokens = preprocess_text(documents[i]);
        all_tokens.push_back(tokens);
    }
    
    for (int doc_id = 0; doc_id < documents.size(); doc_id++) {
        std::vector<std::string> &tokens = all_tokens[doc_id];
        for (int pos = 0; pos < tokens.size(); pos++) {
            std::string word = tokens[pos];

            auto& posting_list = index_dictionary[word];
            bool found_doc = false;

            for (auto& entry: posting_list) {
                if (entry.first == doc_id) {
                    //if already found we append the position only   
                    entry.second.push_back(pos);
                    found_doc = true;
                    break;
                }
            }

            // word appears for the first time
            if (!found_doc) {
                posting_list.push_back({doc_id, {pos}});
            }
        }
    }
    return index_dictionary;
}

int main(){

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

    auto index_dict = build_inverted_index(documents);

    // display inverted index
    for (auto& [word, postings] : index_dict) {
        std::cout << word << " -> ";

        for (auto& entry : postings) {

            int doc_id = entry.first;
            std::vector<int>& positions = entry.second;

            std::cout << "(Doc " << doc_id << ": ";

            for (int pos : positions) {
                std::cout << pos << " ";
            }

            std::cout << ") ";
        }

        std::cout << std::endl;
    }
    std::ofstream myFile("inverted_index.csv");

    if (!myFile.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }
    myFile << "term, [docid,position]\n";
    
    for (auto& [word, postings] : index_dict) {
        myFile << word << ",";

        for (auto& entry : postings) {

            int doc_id = entry.first;
            std::vector<int>& positions = entry.second;

            // myFile << doc_id << ",";

            for (int pos : positions) {
                myFile << doc_id << "," << pos << ",";
            }
        }

        myFile << "\n";
    }
}