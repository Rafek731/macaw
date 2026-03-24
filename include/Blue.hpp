#pragma once
#include "Guesser.hpp"
#include "pattern.hpp"
#include "utils.hpp"
#include <span>

namespace macaw {
    /**
     * @brief
     * Vesion 1 of wordle solver
     * 
     * @details
     * 
     * 
     * @param entropies_
     * vector holding entropy for each word. Index of word correspond to index of its entropy
     * 
     * @param normalization_fn
     * pointer to normalization function for probabilities
     * 
     * @param entropies()
     * returns entropies_
     * 
     * @param calc_entropies()
     * calculates entropies for all allowed words
     * 
     */
    class Blue : public Guesser {

        void (*normalization_fn)(std::vector<double>& v);

        std::vector<double> entropies_;
        std::vector<size_t> order_;

        // void filter_words_(std::string_view word, const Pattern &p);
        // void filter_words_(std::string_view word, std::string_view p);

        public:
        Blue(std::filesystem::path path);
        Blue(std::filesystem::path path, void (*normalizationfn)(std::vector<double> &dist));
        ~Blue() {};

        std::vector<double> entropies() const { return entropies_; }
        void calc_entropies();  

        std::span<size_t> top_guesses(unsigned int num_guesses = 10);
        void guess_made(std::string_view guess, const Pattern& pattern);
    };
}