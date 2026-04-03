from pathlib import Path
from errors import *

from Pattern import Pattern


class Guesser:
    """
    Base class for all guesser models to use in macaw project
    
    It chcecks correctness of given path
    """
    _MAX_LETTERS = 12

    def __init__(self, valid_words):
        Guesser._check_file_correctness()

    def guess_made(self, guess: str, pattern: str|Pattern) -> None:
        if isinstance(pattern, str):
            pattern = Pattern(pattern)
        elif not isinstance(pattern, Pattern):
            raise ValueError(f'This is an invalid pattern: {pattern}')
        

        if len(guess) != len(pattern):
            raise ValueError(f'Pattern should be of the same length as the guess, pattern: {len(pattern)} guess: {guess}')

    def top_guesses(self, n: int = 10) -> list:
        raise NotImplementedError('This method should be overrwritten!')
    
    @property
    def words(self):
        raise NotImplementedError('This method should be overrwritten!')
    
    @staticmethod
    def _check_file_correctness(filepath: str|Path):

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
