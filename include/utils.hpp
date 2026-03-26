#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

namespace macaw {
    // checks if string consists of only characters
    bool alphastr(const std::string &s);


    // namespace for functions that normalize vector probabilities
    namespace normalize {
        void linear(std::vector<double>& v);
        void softmax(std::vector<double>& v);
    }

    /// @todo: better (faster) log2?
    double entropy(const std::vector<double>& dist);

    /**
     * @brief
     * function that sorts vector by values and in descending order and returns indieces to corresponding values
     * 
     * @details 
     * let's say we've got array [4, 5, 2, 9]
     * then sorted indieces list would look like this : [3, 1, 0, 2] 
     * because
     * 
     * @param v 
     * reference to the vector to normalize
     * 
     * @returns
     * indieces - vector of sorted indieces */
    template <typename T>
    std::vector<size_t> argsort(const std::vector<T>& v) {
        std::vector<size_t> indices(v.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&v](size_t i1, size_t i2) { return v[i1] > v[i2]; });

        return indices;
    }
}