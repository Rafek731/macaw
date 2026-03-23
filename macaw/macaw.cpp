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

void macaw::normalize::softmax(std::vector<double> &dist) {
    double sum = 0.0f;
    for(auto &d : dist) {
        d = exp(d);
        sum += d;
    }

    for(auto &d : dist) {
        d /= sum;
    }
}

double macaw::entropy(const std::vector<double>& dist) {
    double ent = 0.0f;
    for(const auto &d : dist) {
        if(d <= 0) continue;
        ent -= d * log2(d);
    }
    return ent;
}

Guesser::Guesser(fs::path path) 
: words_file_(path)
, words_({})
, best_words_({}) { 
    load_words(path); 
} 

bool Guesser::file_correct_() {
    std::fstream file;

    if(!fs::exists(words_file_)) {
        file.close();
        throw std::runtime_error(std::string("File does not exist!"));
        return false;
    }

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
    size_t letters = line.size();
    
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

    if(!file_correct_())
        throw std::runtime_error(std::string("Something wrong with the file!"));

    read_words_();
}

Blue::Blue(fs::path path, void (*normalizationfn)(std::vector<double> &dist)) 
: Guesser(path)
, normalization_fn(normalizationfn) 
, entropies_({})
, order_({}) {
    calc_entropies(); 
}

Blue::Blue(fs::path path) : Blue(path, macaw::normalize::linear) {}

void Blue::calc_entropies() {
    if(words_.empty()) 
        throw std::runtime_error("Words not loaded");

    entropies_.resize(words_.size());

    std::vector<double> dist(static_cast<size_t>(pow(3, words_[0].size())), 0.0);

    for(int i = 0; i < words_.size(); i++) {
        std::string_view word = words_[i];
        std::fill(dist.begin(), dist.end(), 0.0);

        for(std::string_view w : words_) {
            dist[Pattern(word, w).value()] += 1;
        }

        normalization_fn(dist);
        entropies_[i] = entropy(dist);
    }

    order_.resize(entropies_.size());
    order_ = argsort(entropies_);
}

std::span<size_t> Blue::top_guesses(unsigned int num_guesses) {
    num_guesses = (order_.size() >= 10) ? 10 : order_.size();
    return std::span<size_t>(order_).subspan(0, num_guesses);
}

void Blue::guess_made(std::string_view guess, const Pattern& pattern) {
    std::vector<std::string> new_words;
    for(const auto &word : words_) {
        if(Pattern(guess, word) == pattern) {
            new_words.push_back(word);
        }
    }
    
    words_ = std::move(new_words);
    calc_entropies();
}
