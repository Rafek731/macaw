from pathlib import Path
from errors import *

from Pattern import Pattern


class Guesser:
    """
    Base class for all guesser models to use in macaw project
    
    It chcecks correctness of given path and validates users input
    """
    _MAX_LETTERS = 12

    __slots__ = ['valid_words']

    def __init__(self):
        pass

    def guess_made(self, guess: str, pattern: str|Pattern) -> None:
        """Records the guess and pattern given by wordle and performs calculations afterwards"""
        if isinstance(pattern, str):
            for d in pattern:
                if d not in '012':
                    raise InvalidPatternError('Pattern should only consist of \'0\', \'1\' and \'2\'')

        else:
            raise InvalidPatternError(f'This is an invalid pattern: {pattern}')
        

        if len(guess) != len(pattern):
            raise WordError(f'Pattern should be of the same length as the guess, pattern: {len(pattern)} guess: {len(guess)}')
        

    def top_guesses(self, n: int = 10) -> list:
        """Returns list of top n guesses"""
        raise NotImplementedError('This method should be overrwritten!')
    
    @property
    def words(self):
        """Returns current list of possible words"""
        raise NotImplementedError('This method should be overrwritten!')
    
    @staticmethod
    def _check_file_correctness(filepath: str|Path):
        """Checks if the fie is in correct format for loading

        Args:
            filepath (str | Path): Path to the file

        Raises:
            FileNotFoundError: If the file is missing
            EOFError: If the file is empty
            FileProcessingError: If there are some errors related to lengths of words
            ValueError: If words do not consist of letters only
        """
        if isinstance(filepath, str):
            filepath = Path(filepath)

        if not isinstance(filepath, Path):
            raise FileNotFoundError(f'This is not a path to a file: {filepath}')
        
        if not filepath.exists() or not filepath.is_file():
            raise FileNotFoundError(f'This file does not exist: {filepath}')
        
        with open(filepath, 'r') as file:
            all_lines = [line.strip().lower() for line in file.readlines()]
            
            if not all_lines:
                raise EOFError(f'File {filepath} is empty')
            
            words_length = len(all_lines[0])
            
            for line_idx, line in enumerate(all_lines, start = 1): 
                    
                if not line and line_idx != len(all_lines):
                    continue
                elif not line:
                    return
                
                if len(line) != words_length:
                    raise FileProcessingError(f'All words should be of the same length ({words_length}) but word {line} is of length ({len(line)})', 
                                              filepath, 
                                              line_idx)            
                if len(line) > Guesser._MAX_LETTERS:
                    raise FileProcessingError(f'Max supported words length is {Guesser._MAX_LETTERS}, but word is of length {len(line)}',
                                              filepath,
                                              line_idx)
                if not line.isalpha():
                    raise ValueError(f'Words should only contain letters, while the word is {line}',
                                     filepath,
                                     line_idx)
    
    def _load_words(self) -> None:
        """Check file correctness and loads words into memory"""
        self._check_file_correctness()

        with open(self.valid_words, 'r') as file:
            w = [line.strip().lower() for line in file.readlines()]
        
        return w