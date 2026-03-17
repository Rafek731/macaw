#pragma once
#include <filesystem>

namespace macaw {
    typedef uint16_t m_int;
    void read_words(const std::filesystem::path&& path);
    void write_to_file();
    int check_file_correctness(const std::filesystem::path&& path);
}
