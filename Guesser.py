from abc import abstractmethod
from pathlib import Path

from Pattern import Pattern

class Guesser:
    """
    Base class for all guesser models to use in macaw project
    
    It chcecks correctness of given path"""

    def __init__(self, valid_words):
        if isinstance(valid_words, str):
            valid_words = Path(valid_words)
        if not isinstance(valid_words, Path):
            raise ValueError(f'This is not a path to a file: {valid_words}')
        if not valid_words.exists() or not valid_words.is_file():
            raise NameError(f'This file does not exist: {valid_words}')
        
    
    @abstractmethod
    def guess_made(self, guess: str, pattern: str|int|Pattern) -> None:
        raise NotImplementedError('This method should be overrwritten!')
    
    @abstractmethod
    def top_guesses(self, n: int = 10) -> list:
        raise NotImplementedError('This method should be overrwritten!')
    
    @property
    @abstractmethod
    def words(self):
        raise NotImplementedError('This method should be overrwritten!')
    