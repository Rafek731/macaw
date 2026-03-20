#pragma once

#include "pattern.h"

#include <vector>
#include <string>
#include <filesystem>
#include <numeric>
#include <algorithm>

#define MAX_LETTERS 12

namespace macaw {
    // checks if string consists of only characters
    bool alphastr(const std::string &s);


    // namespace for functins that normalize vector probabilities
    namespace normalize {
        void linear(std::vector<double>& v);
        void softmax(std::vector<double>& v);
    }

    // TODO: better log2?
    double entropy(const std::vector<double>& dist);

    /**
     * @brief
     * function that sorts vector by indieces in descending order
     * 
     * @details 
     * let's say we've got array [4, 5, 2, 9]
     * then sorted indieces list would look like this : [3, 1, 0, 2] 
     * because
     * 
     * @param v 
     * vector to normalize
     * 
     * @returns
     * indieces - vector of sorted indieces
     */
    template <typename T>
    std::vector<size_t> argsort(const std::vector<T>& v) {
        std::vector<size_t> indices(v.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&v](size_t i1, size_t i2) { return v[i1] > v[i2]; });

        return indices;
    }

    /**
     * @brief
     * Base class for all wordle sovers. 
     * 
     * @details 
     * It contains functionality like checking if the file
     * with valid words is in correct format, loading valid words to memory and remembering
     * length of words of currently solved wordle
     * 
     * @param words_file_
     * path to file with valid wordle words
     * 
     * @param words_
     * vector of valid wordle words
     * 
     * @param best_words_
     * holds sorted indieces for best words
     * 
     * @param file_correct_() 
     * should return true if file is correct else it throws corresponding errors
     * 
     * @param read_words_() 
     * should only be accessible if `words_file_` is a path to existing file in valid format
     * 
     * @param make_pattern(guess, match)
     * creates trinary representation of wordle pattern between given words
     * 
     * @param words_file()
     * returns words_file_
     * 
     * @param words()
     * returns const reference to words_
     * 
     * @param change_words_path()
     * changes selected flile with valid words and loads it
     * 
     * @param load_words()
     * checks file calls file_correct_() and read_words()
     */
    class Guesser {
        protected:
        std::filesystem::path words_file_;
        std::vector<std::string> words_;
        std::vector<size_t> best_words_;

        bool file_correct_();
        void read_words_();
        
        
        public:
        explicit Guesser(std::string path) : Guesser(std::filesystem::path(path)) {}
        explicit Guesser(std::filesystem::path path) 
        : words_file_(path)
        , words_({})
        , best_words_({}) { 
            load_words(path); 
        } 
        
        ~Guesser() {};
        
        const std::vector<std::string>& words() const { return words_; }
        std::filesystem::path words_file() const { return words_file_; }
        
        unsigned int make_pattern(std::string_view guess, std::string_view match);    
        void load_words(std::filesystem::path path);
    };

    /**
     * @brief
     * Vesion 1 of wordle solver
     * 
     * @details
     * 
     * 
     * @param entropies_
     * vector holding entropy for each word. Index of word correspond to index if its entropy
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

        void sort_by_entropy_();

        // void filter_words_(std::string_view word, const Pattern &p);
        // void filter_words_(std::string_view word, std::string_view p);

        public:
        Blue(std::filesystem::path path) 
        : Guesser(path)
        , normalization_fn(macaw::normalize::linear) 
        , entropies_({}){ 
            entropies_.resize(words_.size()); 
        }

        ~Blue() {};

        std::vector<double> entropies() const { return entropies_; }

        void calc_entropies();  

        std::vector<size_t> top_guesses(unsigned int num_guesses = 10);

        void add_guess(std::string guess, std::string pattern);
    };
}