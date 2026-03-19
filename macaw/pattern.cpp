#include "pattern.h"
#include <iostream>
#include <algorithm>

using namespace macaw;

std::ostream& macaw::operator<<(std::ostream &os, const Pattern &p) {
    unsigned int val = p.value();
    while(val) {
        os << (char)(val % 3 + '0');
        val /= 3;
    }
    return os;
}

void Pattern::print() {
    std::cout << *this << '\n';
}

Pattern& Pattern::operator+=(unsigned int num) {
    this->value_ += num;
    return *this;
}