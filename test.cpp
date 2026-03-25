#include <iostream>
#include "./include/Blue.hpp"

using namespace macaw;

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::span<T> &v) {
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

    for(const auto &idx : m.top_guesses()) {
        std::cout << m.words()[idx] << ": " << m.entropies()[idx] << '\n';
    }

    std::cout << "\n\n\n";
    m.guess_made("tares", Pattern("00100"));

    for(const auto &idx : m.top_guesses()) {
        std::cout << m.words()[idx] << ": " << m.entropies()[idx] << '\n';
    }
    std::cout << "\n\n\n";
    m.guess_made("prion", Pattern("02020"));

    for(const auto &idx : m.top_guesses()) {
        std::cout << m.words()[idx] << ": " << m.entropies()[idx] << '\n';
    }
    std::cout << "\n\n\n";
    m.guess_made("brood", Pattern("22222"));

    for(const auto &idx : m.top_guesses()) {
        std::cout << m.words()[idx] << ": " << m.entropies()[idx] << '\n';
    }
    return 0;
}
