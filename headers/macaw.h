#pragma once
#include <string>

namespace macaw {
    enum colors {
        GREY,
        YELLOW,
        GREEN
    };

    
    class Pattern {
        u_int8_t greens;
        u_int8_t yellows;

        public:
        u_int8_t greens();
        u_int8_t yellows();
        u_int8_t greys();
    };


    class Word : public std::string {
        
        public:
        Pattern compare(const Word &other);
        Pattern operator==(const Word &other);

        bool matches(const Pattern &p);
        bool operator<(const Pattern &p);
    };
}