#pragma once
#include <vector>
#include <string>
#include <filesystem>

#define MAX_LETTERS 12

namespace macaw {
    bool alphastr(const std::string &s);
    namespace normalization {
        void linear(std::vector<double>& v);
        void softmax(std::vector<double>& v);
    }
    // TODO: better log2?
    double entropy(const std::vector<double>& dist);
    

    class Guesser {
        protected:
        std::filesystem::path words_file_;
        std::vector<std::string> words_;
        static unsigned int letters_;
        static unsigned int number_of_patterns;
        bool file_correct_();
        bool read_words_();

        public:
        Guesser() : Guesser(std::filesystem::path(std::string(""))) {}

        explicit Guesser(std::filesystem::path path) : words_file_(std::move(path)), words_({}) {
            if(file_correct_()) read_words_();
        } 
        ~Guesser();

        const std::vector<std::string>& words() const { return words_; }
        
        bool load_words(std::filesystem::path path);
    };

    
    class MacawV1 : public Guesser {
        void (*normalization_fn)(std::vector<double>& v);
        std::vector<double> entropies_;

        public:
        explicit MacawV1(std::string path) : Guesser(std::filesystem::path(path)), normalization_fn(macaw::normalization::linear), entropies_({}) { entropies_.reserve(words_.size()); }
        MacawV1() : MacawV1(std::string("")) {}
        ~MacawV1();

        void calc_entropies();  

        friend unsigned int make_pattern(std::string_view guess, std::string_view match);
    };
}