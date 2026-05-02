#include <iostream>
#include <set>
#include <string>

std::set<std::string> STOP_WORDS = {
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


void preprocess_text(std::string text){
    // text example -> I love Playing Cricket
    std::cout << text << std::endl;

    //lowercase
    int length = text.length();
    for (int i = 0; i < length; i++){
        if(text[i] <= 90 && text[i] >= 65) {
            text[i] = text[i] + 32;
        } else{
            continue;
        }
    }
    
    std::cout << text << std::endl;
    
}

int main() {
    preprocess_text("AZZllo My name IS Pranil ParajULI and I AM CONVERTING upper case TO lOWER case");
}
