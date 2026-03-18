#pragma once
#include "macaw.h"
#include <fstream>
#include <iostream>
#include <math.h>

using namespace macaw;
namespace fs = std::filesystem;

unsigned int powers[11] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};

// Static member definitions
unsigned int macaw::Guesser::letters_ = 0;
unsigned int macaw::Guesser::number_of_patterns = 0;

// Destructor implementations
macaw::Guesser::~Guesser() {}

macaw::MacawV1::~MacawV1() {}

bool macaw::alphastr(const std::string &s) {
    for(int i = 0; i < s.size(); i++) {
        if(!isalpha(s[i])) {
            return false;
        }
    }
    return true;
}

void macaw::normalization::linear(std::vector<double> &dist) {
    double sum = 0;
    for(const auto &d : dist) {
        sum += d;
    }
    
    for(auto &d : dist) {
        d /= sum;
    }
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

    unsigned int p = 0;
    // std::cerr << "initialized" << '\n';
    for(unsigned int i = 0; i < Guesser::letters_; i++) {
        // std::cerr << "i:" << i  << " p:" << p << '\n';
        // std::cerr << "powers: " << powers[Guesser::number_of_patterns - i - 1] << '\n';
        if(guess[i] == match[i]) {
            p += 2 * powers[Guesser::number_of_patterns - i - 1];
            perfect_match[i] = true;
        }

        else {
            remembered_match[match[i]]++;
        }
    }

    for(unsigned int i = 0; i < Guesser::letters_; i++) {
        if(!perfect_match[i] && remembered_match[guess[i]]) {
            p += powers[MacawV1::letters_ - i - 1];
            remembered_match[guess[i]]--;
        }
    }
    return p;
}

double macaw::entropy(const std::vector<double>& dist) {
    double ent;
    for(const auto &d : dist) {
        if(d <= 0.00000001) continue;
        ent -= d * log2(d);
    }
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
    // std::cerr << "leters_ = " << Guesser::letters_ << '\n';
    std::vector<double> dist(number_of_patterns, 0);
    // std::cerr << "dist created" << '\n';
    for(int i = 0; i < words_.size(); i++) {
        if(i % 100 == 0) {
            // std::cerr << i << '\n';
        }

        std::fill(dist.begin(), dist.end(), 0.);
        // std::cerr << "dist filled with 0s" << '\n';
        entropies_[i] = 0;
        std::string_view word = words_[i];

        for(std::string_view w : words_) {
            dist[make_pattern(word, w)] += 1;
        }
        double sum = 0;
        // std::cerr << "Distribution " << '\n';
        for(const auto &d : dist) {
            // std::cerr << d << ' ';
            sum += d;
        }
        // std::cerr <<"\nsum: " << sum << '\n';

        // std::cerr << '\n';

        normalization_fn(dist);
        double e = entropy(dist);
        // std::cerr << "entropy: " << e << '\n';
        entropies_[i] = e;
    }
}


