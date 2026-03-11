#pragma once
#include <string>
#include <iostream>

namespace macaw {
    enum colors {
        GREY,
        YELLOW,
        GREEN
    };

    
    class Pattern {
        /**
         * pattern is stred as a number in trinary system where
         * 2 = green
         * 1 = yellow
         * 0 = gray
         * this way for example pattern [green green gray gray yellow] has value:
         * 2*3^4+ 2*3^3 + 0*3^2 + 0*3^1 + 1*3^0 = 211
         * 
         */
        u_int16_t value;

        public:
        Pattern() : value(0) {};
        Pattern(int n) : value(n) {};
        Pattern(Word &w1, Word &w2);

        void print();
        Pattern& operator=(Pattern &&p);
    };


    class Word : public std::string {
        
        public:
        Pattern compare(const Word &other);
        Pattern operator==(const Word &other);

        bool matches(const Pattern &p);
        bool operator<(const Pattern &p);
    };
}