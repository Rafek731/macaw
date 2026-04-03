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

void Guesser::load_words(fs::path path) {
    words_file_ = path;

    std::fstream file;
    std::string line;

    file.open(words_file_.string(), std::ios::in);

    words_.clear();
    while(getline(file, line))
        words_.push_back(line);

    file.close();
}