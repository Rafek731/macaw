#include <cmath>

#include "../include/Blue.hpp"

using namespace macaw;
namespace fs = std::filesystem;

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
