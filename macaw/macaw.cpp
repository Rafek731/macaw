#pragma once
#include "macaw.h"
#include <fstream>
#include <iostream>

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
    const short words_length = line.size();
    
    if(!alphastr(line)) {
        file.close();
        throw std::runtime_error(std::string("This is not a word: ") + line);
        return false;
    }
    
    while(!file.eof()) {
        getline(file, line); 

        if(line.size() != words_length) {
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
    return true;
}