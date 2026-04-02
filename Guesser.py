from abc import abstractmethod
from Pattern import Pattern

class Guesser:
    """Base class for all guesser models to use in macaw project"""
    @abstractmethod
    def __init__(self):
        pass
    
    @abstractmethod
    def guess_made(guess: str, pattern: str|int|Pattern) -> None:
        pass
    
    @abstractmethod
    def top_guesses(n: int = 10) -> list:
        pass