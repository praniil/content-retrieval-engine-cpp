#include <iostream>
#include <set>
#include <vector>
#include <string>
#include<sstream>

std::vector<std::string> STOP_WORDS = {
    "a", "an", "and", "the", "or", "of", "to", "in", "for", "on", "with",
    "at", "by", "i", "you", "he", "she", "it", "we", "they", "me", "him",
    "her", "us", "them", "my", "your", "his", "its", "our", "their", "this",
    "that", "these", "those", "is", "are", "was", "were", "be", "been", "being",
    "have", "has", "had", "do", "does", "did", "will", "would", "shall", "should",
    "may", "might", "must", "can", "could", "as", "but", "if", "or", "because",
    "until", "while", "of", "at", "by", "for", "with", "about", "against", "between",
    "into", "through", "during", "before", "after", "above", "below", "from", "up",
    "down", "in", "out", "on", "off", "over", "under", "again", "further", "then",
    "once", "here", "there", "when", "where", "why", "how", "all", "any", "both",
    "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not",
    "only", "own", "same", "so", "than", "too", "very"
};

std::vector<std::string> PUNCTUATION = {
    ".", ",", "?", "!", ";", ":", "'", "\"",
    "(", ")", "[", "]", "{", "}",
    "-", "—", "…"
};

//simpleStemmer logic
std::string simpleStemmer(std::string word) {
    // 'ing', 'ly', 'ed', 'es', 's'
    if (word.length() > 4) {
        if (word.substr(word.length() - 3) == "ing") {
            return word.substr(0, word.length() - 3);
        }
        if (word.substr(word.length() - 2 )== "ly") {
            return word.substr(0, word.length() - 2);
        }
        if (word.substr(word.length() - 2 )== "ed") {
            return word.substr(0, word.length() - 2);
        }
        if (word.substr(word.length() - 2 )== "es") {
            return word.substr(0, word.length() - 2);
        }
        if (word.substr(word.length() - 1 )== "s") {
            return word.substr(0, word.length() - 1);
        }
    }
    return word;
}

std::vector<std::string> preprocess_text(std::string text){
    //lowercase
    int length = text.length();
    for (int i = 0; i < length; i++){
        if(text[i] <= 90 && text[i] >= 65) {
            text[i] = text[i] + 32;
        } else{
            continue;
        }
    }

    //remove punctuations
    for (int i = 0; i< text.length(); i++) {
        for (int j = 0; j < PUNCTUATION.size(); j++) {
            if (text[i] == PUNCTUATION[j][0]) {
                text.erase(i, 1);
                i--;
                break;
            }else {
                continue;
            }
        }
    }

    // tokenizer
    std::vector<std::string> tokens;
    std::stringstream ss(text);     //converthing the string into a stream, now we can extract words from it just like cin
    std::string word;
    
    while(ss >> word) {
        tokens.push_back(word);
    }
    
    //remove the stop words
    for (int i = 0; i < tokens.size(); i++){
        for (int j = 0; j < STOP_WORDS.size(); j++) {
            if (tokens[i] == STOP_WORDS[j]) {
                tokens.erase(tokens.begin() + i);
                i--;
                break;
            } else {
                continue;
            }
        }
    }

    std::vector<std::string> stemmedTokens;
    // stemming the tokens
    for (int i = 0; i < tokens.size(); i++) {
        std::string stemmed_token = simpleStemmer(tokens[i]);
        stemmedTokens.push_back(stemmed_token);
    }
    
    return stemmedTokens;
}
