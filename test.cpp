#include <iostream>
#include "macaw/macaw.h"

using namespace macaw;


int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    MacawV1 m("./valid_words.txt");
    
    for(const auto &w: m.words()) {
        std::cout << w << '\n';
    }

    m.calc_entropies();
    for(const auto &e : m.entropies()){
        std::cout << e << ' ';
    }
    std::cout << '\n';
    m.sort_entropies();
    
    return 0;
}