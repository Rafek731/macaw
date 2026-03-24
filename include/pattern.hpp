#pragma once

#include <iostream>
#include <string>

#define MAX_LETTERS 12

namespace macaw {
    class Pattern {
        /**
         * pattern is stored as a number in reverse (left to right) trinary system where
         * 2 = green
         * 1 = yellow
         * 0 = gray
         * this way for example pattern [green green gray gray yellow] has value:
         * 2*3^0+ 2*3^1 + 0*3^2 + 0*3^3 + 1*3^4 = 89 */
        protected:
        unsigned int value_;

        public:

        Pattern(const unsigned int n);
        Pattern(std::string_view guess, std::string_view match);
        Pattern(std::string_view pattern);

        unsigned int value() const { return value_; }
        std::string string(const size_t fields = 0) const;

        bool operator==(const Pattern &other) const { return this->value_ == other.value_; }
    };

    std::ostream& operator<<(std::ostream& os, const Pattern &p);
}