#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <numeric>
#include <algorithm>

#define MAX_LETTERS 12

namespace macaw {
    bool alphastr(const std::string &s);

    namespace normalize {
        void linear(std::vector<double>& v);
        void softmax(std::vector<double>& v);
    }

    // TODO: better log2?
    double entropy(const std::vector<double>& dist);

    template <typename T>
    std::vector<size_t> argsort(const std::vector<T>& v) {
        std::vector<size_t> indices(v.size());

        std::iota(indices.begin(), indices.end(), 0);

        std::sort(indices.begin(), indices.end(), [&v](size_t i1, size_t i2) { return v[i1] > v[i2]; });

        return indices;
    }

    /**
     * words_file_
     *      path to file with valid wordle words
     * 
     * words_
     *      vector of valid wordle words
     * 
     * file_correct_() 
     *      should return true if file is correct else it throws corresponding errors
     * 
     * read_words_() 
     *      should only be accessible if `words_file_` is a path to existing file in valid format
     * 
     * make_pattern(guess, match)
     *      creates trinary representation of wordle pattern between given words
     * 
     * letters_
     *      holds length of words in 
     * 
     * number_of_patterns
     *      number of possible wordle patterns (just 3 ** letters_)
     * 
     * words_file()
     *      returns words_file_
     * 
     * words()
     *      returns const reference to words_
     * 
     * change_words_path()
     *      changes selected flile with valid words and loads it
     * 
     * load_words()
     *      checks file calls file_correct_() and read_words()
     */
    class Guesser {
        protected:
        std::filesystem::path words_file_;
        std::vector<std::string> words_;

        bool file_correct_();
        void read_words_();
        
        
        public:
        unsigned int letters_;
        unsigned int number_of_patterns;
        explicit Guesser(std::string path) : Guesser(std::filesystem::path(path)) {}
        explicit Guesser(std::filesystem::path path) 
        : words_file_(path)
        , words_({}) { 
            load_words(path); 
        } 
        
        ~Guesser();
        
        const std::vector<std::string>& words() const { return words_; }
        std::filesystem::path words_file() const { return words_file_; }
        
        unsigned int make_pattern(std::string_view guess, std::string_view match);    
        void load_words(std::filesystem::path path);
    };

    
    class MacawV1 : public Guesser {

        void (*normalization_fn)(std::vector<double>& v);
        
        std::vector<double> entropies_;

        public:

        MacawV1(std::filesystem::path path) 
        : Guesser(path)
        , normalization_fn(macaw::normalize::linear) 
        , entropies_({}) { 
            entropies_.resize(words_.size()); 
        }
        
        MacawV1() : MacawV1(std::string("")) {}
        ~MacawV1();

        std::vector<double> entropies() const {return entropies_; }
        
        void calc_entropies();  
        void sort_entropies();

    };
}