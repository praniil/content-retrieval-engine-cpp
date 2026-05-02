#include <iostream>
#include <set>
#include <vector>
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

std::vector<std::string> PUNCTUATION = {
    ".", ",", "?", "!", ";", ":", "'", "\"",
    "(", ")", "[", "]", "{", "}",
    "-", "—", "…"
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
    std::cout << "before punctuation removal: " << std::endl;
    std::cout << text << std::endl;    

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


    std::cout << "after punctuation removal: " << std::endl;
    std::cout << text << std::endl;
    
}

int main() {
    preprocess_text("AZZllo???? My name IS Pranil[] ParajULI an!d I AM CONVERTING\" upper case TO lOWER case");
}
