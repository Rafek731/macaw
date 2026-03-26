from setuptools import Extension, setup
from pybind11.setup_helpers import Pybind11Extension 

ext_modules = [
    Pybind11Extension(
        "macaw",  # Module name
        ["src/Blue.cpp", "src/Guesser.cpp", "src/pattern.cpp", "src/utils.cpp", "src/macaw.cpp"],  # Source files
        extra_compile_args=['-std=c++23', '-O3']
    )
]

setup(
    name="macaw",
    version="0.1",
    ext_modules=ext_modules,
)