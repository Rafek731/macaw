#pragma once

#include "iooperations.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace macaw {

    typedef uint16_t m_int;

    int check_file_correctness(const std::filesystem::path &&path) {
        std::fstream file;
        file.open(path.string(), std::ios::in);
        std::string line; 

        if(!file.good()) {
            throw std::runtime_error("Cant open the file: " + path.string());
        }

        short words_length = 0;

        if(!file.eof()){
            getline(file, line);
            words_length = line.size();
        }
        
        while(!file.eof()) {
            getline(file, line);

            if(line.size() != words_length) {
                throw std::runtime_error("Different lengths of words!");
            }
        }

        file.close();
        return 1;
    }

}