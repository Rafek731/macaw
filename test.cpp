#include <iostream>
#include "macawV1/macaw.h"

using namespace macaw;


int main(void) {
    MacawV1 m;
    m.load_words(std::string("./valid_words.txt"));
    return 0;

}