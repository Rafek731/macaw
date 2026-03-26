"""
Macaw - Wordle solver module
"""
from __future__ import annotations
__all__: list[str] = ['Blue']

class Blue:
    def __init__(*args, **kwargs) -> None:
        """
        First model for Worlde solving developed by Rafal Mazur
        """
    def guess_made(*args, **kwargs) -> None:
        """
        Gathers inforamtion given by wordle and computes entropies
        """
    def top_guesses(*args, **kwargs) -> list[tuple[str, float]]:
        """
        returns pairs of (word, entropy) of best guesses
        """
    def calc_entropies(self) -> None:
        """
        Calculates entropies
        """
    def entropies(self) -> list[float]:
        """
        list of current entropies on indieces corresponding to the words
        """
