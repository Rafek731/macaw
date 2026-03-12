#pragma once
#include "pattern.h"

namespace macaw {
    class Word {
        protected:
        std::string content_;

        public:
        static size_t letters;
        Word(std::string str) : content_(str) {};
        Word() : Word(std::string("")) {};

        std::string content() const;
        char operator[](size_t idx) const;

        Pattern operator&(const Word &match);
        friend std::ostream& operator<<(std::ostream &os, const Word &word);
        friend macint make_pattern(const Word &guess, const Word &match);
    };
    
    
}