#pragma once
#include <filesystem>
#include <string>

namespace macaw {
    void read_words(const std::filesystem::path&& path);
    void write_to_file();
    void check_file_correctness(const std::filesystem::path&& path);
}
