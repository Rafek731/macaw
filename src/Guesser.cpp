#include <fstream>

#include "../include/Guesser.hpp"
#include "../include/utils.hpp"

using namespace macaw;
namespace fs = std::filesystem;

Guesser::Guesser(fs::path path) 
: words_file_(path)
, words_({}) { 
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
