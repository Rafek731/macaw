#pragma once

#include "word.h"
#include "queue.h"
static macint powers[] = {1, 3, 9, 27, 81, 243, 728, 2187, 6561, 19683, 59049};

#ifndef MAX_LETTERS
#define MAX_LETTERS 12
#endif

namespace macaw {

size_t Word::letters = 5;

char Word::operator[](size_t idx) const {
    return content_[idx];
}

std::string Word::content() const {
    return content_;
}

std::ostream& operator<<(std::ostream &os, const Word &word) {
    os << word.content_;
    return os;
}

/**
 * algorithm goes like this:
 * iterate through both words first time
 * if two values match:
 *      add green value on apropriate postion to p
 *      mark it as perfect match 
 * else:
 *      remember that this letter occured (add it to occurance count)
 * 
 * iterate through both words second time without perfect matches
 * if value exists in match add yellow value on apropriate postion to p
 * 
 * retrun p
 */
macint make_pattern(const Word &guess, const Word &match) {
    /**
     * table containing positions of seen letters (not ones perfectly matched)
     * e.g.
     * match = alial
     * guess = aalle
     * patt  = 21110
     * 
     * remembered_match['a'] = (3)
     * remembered_match['l'] = (1, 4)
     * remembered_match['i'] = (2)
     * 
     * so when we go through '1's on guess we can chech if a letter exists in match
     * in O(1) time and then 
     * 
     */
    char remembered_match[128]{0};
    bool perfect_match[MAX_LETTERS]{0};

    macint p;
    for(char i = 0; i < Word::letters; i++) {
        if(guess[i] == match[i]) {
            p += 2 * powers[Word::letters - i - 1];
            perfect_match[i] = true;
        }

        else {
            remembered_match[match[i]]++;
        }
    }

    for(int i = 0; i < Word::letters; i++) {
        if(!perfect_match[i] && remembered_match[guess[i]]) {
            p += powers[Word::letters - i - 1];
            remembered_match[guess[i]]--;
        }
    }

    return p;
}

} // namespace macaw

