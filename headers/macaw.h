#pragma once
#include <string>

namespace macaw {
    enum colors {
        GREY,
        YELLOW,
        GREEN
    };

    
    class Pattern {
        int16_t greens;
        int16_t yellows;

        public:
        int16_t greens();
        int16_t yellows();
        int16_t greys();
    };


    class Word : public std::string {
        
        public:
        Pattern compare(const Word &other);
        Pattern operator==(const Word &other);

        bool matches(const Pattern &p);
        bool operator<(const Pattern &p);
    };
}