#pragma once
#include "macaw.h"
#include <fstream>
#include <iostream>
#include <math.h>

using namespace macaw;
namespace fs = std::filesystem;




bool macaw::alphastr(const std::string &s) {
    for(int i = 0; i < s.size(); i++) {
        if(!isalpha(s[i])) {
            return false;
        }
    }
    return true;
}

void macaw::normalize::linear(std::vector<double> &dist) {
    double sum = 0;

    for(const auto &d : dist)
        sum += d;
    
    for(auto &d : dist)
        d /= sum;
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

double macaw::entropy(const std::vector<double>& dist) {
    double ent = 0.0f;
    for(const auto &d : dist) {
        if(d <= 0) continue;
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
    unsigned int letters = line.size();
    
    if(line.size() > MAX_LETTERS) {
        throw std::runtime_error("Word is too long");
    }
    
    if(!alphastr(line)) {
        file.close();
        throw std::runtime_error(std::string("This is not a word: ") + line);
        return false;
    }
    
    while(getline(file, line)) {
        if(line.size() != letters) {
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

void Guesser::read_words_() {
    std::fstream file;
    std::string line;
    
    file.open(words_file_.string(), std::ios::in);

    words_.clear();
    while(getline(file, line))
        words_.push_back(line);

    file.close();
    
}

void Guesser::load_words(fs::path path) {

    words_file_ = path;
    if(!fs::exists(words_file_))
        throw std::runtime_error(std::string("File does not exist!"));
    

    if(!file_correct_())
        throw std::runtime_error(std::string("File is in incorrect format!"));

    read_words_();
}

void Blue::sort_by_entropy_() {
    std::vector<size_t> indecies = argsort(entropies_);
}

void Blue::calc_entropies() {
    if(words_.empty()) 
        throw std::runtime_error("Words not loaded");

    entropies_.resize(words_.size());

    std::vector<double> dist(pow(3, words_[0].size()), 0.0);

    for(int i = 0; i < words_.size(); i++) {
        std::string_view word = words_[i];
        std::fill(dist.begin(), dist.end(), 0.0);

        for(std::string_view w : words_) {
            dist[Pattern(word, w).value()] += 1;
        }

        normalization_fn(dist);
        entropies_[i] = entropy(dist);
    }
}

std::vector<size_t> Blue::top_guesses(unsigned int num_guesses = 10) {
    num_guesses = (words_.size() >= 10) ? 10 : words_.size();
    std::vector<size_t> indieces = argsort(entropies_);
    indieces.resize(num_guesses);
    return indieces;
}
// void Blue::filter_words_(std::string_view word, std::string_view p) {
// }

// void Blue::filter_words_(std::string_view word, const Pattern &p) {
//     std::vector<std::string> new_words;
//     for(const std::string &w : words_) {
//         if(Pattern(word, w) == p) {
//             new_words.push_back(w);
//         }
//     }

    
// }

// void Blue::make_guess(std::string guess, std::string response) {


// }

