from dataclasses import dataclass

@dataclass(frozen=True)
class Pattern:
    """
    Class representing patterns made by wordle

    Enables easy creation of patterns between words and eye-pleasing display
    """
    __slots__ = ['value']
    _value: int
    """
    Pattern is represented by a number in trinary system read from left to right (least significant digit on the left)
    e.g 🟩⬛⬛🟩🟨 = (20021)3 = 137; because 2 * 1 + 0 * 3 + 0 * 9 + 2 * 27 + 1 * 81 = 137 
    """

    def __init__(self, guess: str, match: str):
        # if the letter doesnt match add it to new_guess and new_match otherwise inser special
        # character so that it wont match again in another round
        self._value = 0
        
        

    def __str__(self):
        pass

    def __repr__(self):
        pass
