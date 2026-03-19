#include <iostream>
#include "macaw/macaw.h"
#include "macaw/pattern.h"

using namespace macaw;

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    os << '[';
    if(v.size() <= 50){
        for(const auto& element : v) 
            os << element << ' ';
         
    }
    else {
        for(int i=0; i < 30; i++)
            os << v[i] << ' ';
        os << "... ";
        for(int i=v.size() - 5; i < v.size(); i++)
            os << v[i] << ' ';
    }
    os << "\b]\n";
    return os; 
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    Blue m("./valid_words.txt");
    
    std::cout << m.words();

    m.calc_entropies();
    m.sort_entropies();
    std::cout << m.entropies();
    
    Pattern p(m.make_pattern("doggo", "foieg"));
    std::cout << "foieg" << '\n';
    std::cout << "doggo" << '\n';
    std::cout << p << '\n';
    std::cout << p.value() << '\n';
    return 0;
}