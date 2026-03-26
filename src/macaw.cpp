#include <pybind11/pybind11.h>
#include "../include/macaw.hpp"

PYBIND11_MODULE(macaw, m) {
    m.doc() = "Macaw - Wordle solver module";

    pybind11::class_<macaw::Blue>(m, "Blue")

    .def(pybind11::init<std::string>(),
        "First model for Worlde solving developed by Rafal Mazur",
        pybind11::arg("valid_words_path (str): path to file containing valid words for wordle game"))

    .def("guess_made", &macaw::Blue::guess_made, 
        "Gathers inforamtion given by wordle and computes entropies",
        pybind11::arg("guess (str): word you typed into wordle"),
        pybind11::arg("pattern (str): pattern that wordle spilled out e.g. 22021"))

    .def("top_guesses", &macaw::Blue::top_guesses,
        "returns pairs of (word, entropy) of best guesses",
        pybind11::arg("num_guesses (int): number of top guesses to return"))

    .def("entropies", &macaw::Blue::entropies,
        "list of current entropies on indieces corresponding to the words")
    .def("calc_entropies", &macaw::Blue::calc_entropies,
        "Calculates entropies");
}