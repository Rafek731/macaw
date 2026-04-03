#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include "pattern.hpp"

namespace macaw {
    /**
     * @brief
     * Base class for all wordle sovers. 
     * 
     * @details 
     * It contains functionality like checking if the file
     * with valid words is in correct format, loading valid words to memory 
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
     * checks file calls file_correct_() and read_words() */


    class Guesser {
        protected:
        std::filesystem::path words_file_;
        std::vector<std::string> words_;
        
        public:
        explicit Guesser(std::string path) : Guesser(std::filesystem::path(path)) {}
        explicit Guesser(std::filesystem::path path);
        
        const std::vector<std::string>& words() const { return words_; }
        std::filesystem::path words_file() const { return words_file_; }
          
        void load_words(std::filesystem::path path);
    };
}