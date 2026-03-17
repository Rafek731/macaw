#pragma once
#include "macaw.h"
#include <fstream>
#include <iostream>
#include <math.h>

using namespace macaw;
namespace fs = std::filesystem;

static unsigned int powers[] = {1, 3, 9, 27, 81, 243, 728, 2187, 6561, 19683, 59049};

bool macaw::alphastr(const std::string &s) {
    for(int i = 0; i < s.size(); i++) {
        if(!isalpha(s[i])) {
            return false;
        }
    }
    return true;
}

void macaw::normalization::linear(const std::vector<double> &dist) {
    
}

/**
 * algorithm goes like this:
 * iterate through both words first time
 * if two values match:
 *      add green value on apropriate postion to p
 *      mark it as perfect match 
 * else:
 *      remember that this letter occured (add it to remembered_match)
 * 
 * iterate through both words second time without perfect matches
 * if value exists in match add yellow value on apropriate postion to p
 * 
 * retrun p
 */
unsigned int macaw::make_pattern(std::string_view guess, std::string_view match) {
    /** remembered_match
     * table containing positions of seen letters (not ones perfectly matched)
     * e.g.
     * match = alial
     * guess = aalle
     * patt  = 21110
     * 
     * remembered_match['a'] = (3)
     * remembered_match['l'] = (1, 4)
     * remembered_match['i'] = (2)
     * 
     * so when we go through '1's on guess we can chech if a letter exists in match
     * in O(1) time and then 
     */

    char remembered_match[128]{0};
    bool perfect_match[MAX_LETTERS]{0};

    unsigned int p;
    for(unsigned int i = 0; i < MacawV1::letters_; i++) {
        if(guess[i] == match[i]) {
            p += 2 * powers[MacawV1::number_of_patterns - i - 1];
            perfect_match[i] = true;
        }

        else {
            remembered_match[match[i]]++;
        }
    }

    for(unsigned int i = 0; i < MacawV1::letters_; i++) {
        if(!perfect_match[i] && remembered_match[guess[i]]) {
            p += powers[MacawV1::letters_ - i - 1];
            remembered_match[guess[i]]--;
        }
    }

    return p;
}

double macaw::entropy(const std::vector<double>& dist) {
    double ent;
    for(const auto &d : dist)
        ent -= d * log2(d);
    return ent;
}

bool Guesser::file_correct_() {
    std::fstream file;
    file.open(words_file_.string(), std::ios::in);
    std::string line; 

    if(!file.good()) {
        file.close();
        throw std::runtime_error(std::string("Problems with the file: ") + words_file_.string());
        return false;
    }
    
    if(file.eof()){
        file.close();
        throw std::runtime_error(std::string("Empty file: ") + words_file_.string());
        return false;
    }

    getline(file, line); 
    letters_ = line.size();
    
    if(letters_ > MAX_LETTERS) {
        throw std::runtime_error("Word is too long");
    }
    
    if(!alphastr(line)) {
        file.close();
        throw std::runtime_error(std::string("This is not a word: ") + line);
        return false;
    }
    
    while(!file.eof()) {
        getline(file, line); 

        if(line.size() != letters_) {
            file.close();
            throw std::runtime_error(std::string("Different lengths of words!"));
            return false;
        }

        if(!alphastr(line)) {
            file.close();
            throw std::runtime_error(std::string("This is not a word: ") + line);
            return false;
        }
    }

    file.close();
    return true;
}

bool Guesser::load_words(fs::path path) {
    words_file_ = path;
    if(!fs::exists(words_file_)) {
        throw std::runtime_error(std::string("File does not exist!"));
        return false;
    }
    
    if(!file_correct_()) {
        throw std::runtime_error(std::string("File is in incorrect format!"));
        return false;
    }
    
    read_words_();
    return true;
}

bool Guesser::read_words_() {
    std::fstream file;
    std::string line;

    file.open(words_file_.string(), std::ios::in);

    while(!file.eof()) {
        getline(file, line);
        words_.push_back(line);
    }

    file.close();
    
    letters_ = words_[0].size();
    number_of_patterns = 1;
    for(int i=0; i < letters_; i++){
        number_of_patterns *= 3;
    }
    
    return true;
}

void MacawV1::calc_entropies() {
    if(words_.empty()) {
        throw std::runtime_error("Words not loaded");
    }

    std::vector<double> dist(number_of_patterns, 0);

    for(int i = 0; i < words_.size(); i++) {
        std::fill(dist.begin(), dist.end(), 0.);
        entropies_[i] = 0;
        std::string_view word = words_[i];

        for(std::string_view w : words_) {
            dist[make_pattern(word, w)] += 1;
        }

        normalization_fn(dist);
        entropies_[i] = entropy(dist);
    }
}

