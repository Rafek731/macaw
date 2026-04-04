from Guesser import Guesser
import macaw
from pathlib import Path
from errors import WordError

class Blue(Guesser):
    """Wordle solving model which backend is written in C++ in order to perform in real time"""

    def __init__(self, valid_words: Path|str):
        super().__init__()
        self._check_file_correctness()
        self._guesser = macaw.Blue(valid_words)
        self.words_length = len(self._guesser.words()[0])

    def top_guesses(self, n = 10) -> list[tuple[str, float]]:
        """Returns top n current guesses-entropy pairs

        Args:
            n (int, optional): number of guesses to show. Defaults to 10.

        Returns:
            list[tuple[str, float]]: list of pairs (word, entropy) in best to worst order
        """
        return self._guesser.top_guesses(n)
    
    def guess_made(self, guess: str, pattern: str) -> None:
        """Tells the guesser what choice was made and what pattern did wordle generate

        Args:
            guess (str): guess typed into wordle
            pattern (str): pattern that wordle generated, e.g. if pattern is 🟩⬛⬛🟩🟨 then type 20021, because
            🟩 = 2, 🟨 = 1, ⬛ = 0 
        """

        if guess not in self.words:
            raise WordError(f'Word {guess} is not a possible word to be the answer')
        
        if len(guess) != len(pattern):
            raise WordError(f'Guess and pattern should be of the same length')

        return self._guesser.guess_made(guess, pattern)
    
    @property
    def words(self) -> list[str]:
        return self._guesser.words()