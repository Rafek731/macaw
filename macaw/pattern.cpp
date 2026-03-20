#include "pattern.h"
#include <iostream>
#include <algorithm>

using namespace macaw;

static unsigned int powers[11] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};

std::ostream& macaw::operator<<(std::ostream &os, const Pattern &p) {
    os << p.string();
    return os;
}

std::string Pattern::string() const {
    std::string result = "";
    unsigned int val = value_;

    while(val) {
        result += (char)(val % 3 + '0');
        val /= 3;
    }

    return result;
}

void Pattern::print() {
    std::cout << *this << '\n';
}

Pattern::Pattern(std::string_view pattern) {
    value_ = 0;
    unsigned int mul = 1;
    for(const auto &c : pattern) {
        value_ += (c - '0') * mul;
        mul *= 3;
    }

}

Pattern::Pattern(std::string_view guess, std::string_view match){
    char remembered_match[128]{0};
    bool perfect_match[MAX_LETTERS]{0};

    value_ = 0;

    for(unsigned int i = 0; i < guess.size(); i++) {
        if(guess[i] == match[i]) {
            value_ += 2 * powers[i];
            perfect_match[i] = true;
        }
        else remembered_match[match[i]]++;
    }

    for(unsigned int i = 0; i < guess.size(); i++) {
        if(!perfect_match[i] && remembered_match[guess[i]]) {
            value_ += powers[i];
            remembered_match[guess[i]]--;
        }
    }
}