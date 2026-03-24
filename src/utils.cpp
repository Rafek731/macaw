#include <cmath>

#include "../include/utils.hpp"

using namespace macaw;

bool macaw::alphastr(const std::string &s) {
    for(int i = 0; i < s.size(); i++) {
        if(!isalpha(s[i])) {
            return false;
        }
    }
    return true;
}

void macaw::normalize::linear(std::vector<double> &dist) {
    double sum = 0;

    for(const auto &d : dist)
        sum += d;
    
    for(auto &d : dist)
        d /= sum;
}

void macaw::normalize::softmax(std::vector<double> &dist) {
    double sum = 0.0f;
    for(auto &d : dist) {
        d = exp(d);
        sum += d;
    }

    for(auto &d : dist) {
        d /= sum;
    }
}

double macaw::entropy(const std::vector<double>& dist) {
    double ent = 0.0f;
    for(const auto &d : dist) {
        if(d <= 0) continue;
        ent -= d * log2(d);
    }
    return ent;
}
