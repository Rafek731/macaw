#pragma once

#define macint u_int16_t

#include <iostream>
#include "word.h"

namespace macaw {
    class Pattern {
            /**
             * pattern is stored as a number in trinary system where
             * 2 = green
             * 1 = yellow
             * 0 = gray
             * this way for example pattern [green green gray gray yellow] has value:
             * 2*3^4+ 2*3^3 + 0*3^2 + 0*3^1 + 1*3^0 = 211
             * */
            protected:
            macint value;

            public:
            Pattern() : value(0) {};
            Pattern(macint n) : value(n) {};

            void print();
            Pattern& operator+=(macint num);
            friend std::ostream& operator<<(std::ostream& os, Pattern &p);
        };

        std::ostream& operator<<(std::ostream& os, Pattern &p);
}