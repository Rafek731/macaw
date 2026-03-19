#pragma once

#include <iostream>

namespace macaw {
    class Pattern {
            /**
             * pattern is stored as a number in reverse (left to right) trinary system where
             * 2 = green
             * 1 = yellow
             * 0 = gray
             * this way for example pattern [green green gray gray yellow] has value:
             * 2*3^0+ 2*3^1 + 0*3^2 + 0*3^3 + 1*3^4 = 89
             * */
            protected:
            unsigned int value_;

            public:
            explicit Pattern(unsigned int n) : value_(n) {};
            unsigned int value() const { return value_; }
            

            void print();
            Pattern& operator+=(unsigned int num);

        };
        std::ostream& operator<<(std::ostream& os, const Pattern &p);
}