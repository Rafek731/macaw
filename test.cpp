#include "cppfiles/word.h"
#include <iostream>

using namespace macaw;

int main(void) {
    Word  guess(std::string("abaaa"));
    Word answer(std::string("babbb"));
    std::cout << make_pattern(guess, answer) << '\n';
    return 0;
}