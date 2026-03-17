#pragma once
#include <vector>
#include <string>
#include <filesystem>


namespace macaw {
    typedef uint16_t m_int;
    typedef double m_float;

    bool alphastr(const std::string &s);

    class Guesser {
        protected:
        std::filesystem::path words_file_;
        std::vector<std::string> words_;
        bool file_correct_();
        bool read_words_();

        public:
        Guesser() : Guesser(std::filesystem::path(std::string(""))) {}

        explicit Guesser(std::filesystem::path path) : words_file_(std::move(path)), words_({}) {
            if(file_correct_()) read_words_();
        } 

        const std::vector<std::string>& words() const { return words_; }
        
        bool load_words(std::filesystem::path path);
    };

    
    class MacawV1 : public Guesser {
        std::vector<m_int> calc_distribution(m_int idx);
        
        public:
        std::vector<m_float> entropies;
    
        MacawV1(std::string path) : Guesser(std::filesystem::path(path)) {}
        MacawV1() : MacawV1(std::string("")) {}

        void calc_entropies();    
        
        friend m_int make_pattern(std::string_view guess, std::string_view match);
        friend m_float entropy(const std::vector<m_float>& dist);
    };
}