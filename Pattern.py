from multipledispatch import dispatch
class Pattern:
    """
    Class representing patterns made by wordle

    Enables easy creation of patterns between words and eye-pleasing display
    """
    __slots__ = ['_value', '_words_length']
    _value: int
    """
    Pattern is represented by a number in trinary system read from left to right (least significant digit on the left)
    e.g 🟩⬛⬛🟩🟨 = (20021)3 = 137; because 2 * 1 + 0 * 3 + 0 * 9 + 2 * 27 + 1 * 81 = 137 
    """
    _words_length: int
    """Holds lengt of words that the pattern was generated for"""
    @dispatch(str, str)
    def __init__(self, guess: str, answer: str) -> None:
        assert len(guess) == len(answer), f'Lengts of words \'{guess}\' and \'{answer}\' are different!'
        guess = guess.lower()
        answer = answer.lower()

        self._words_length = len(guess)
        self._value = 0

        guess = list(guess)
        answer = list(answer)

        # if the letter doesnt match add it to new_guess and new_match otherwise inser special
        # character so that it wont match again in another round
        for i, (g, m) in enumerate(zip(guess, answer)):
            if g == m:
                self._value += 2 * 3**i
                guess[i] = '@'
                answer[i] = '#'

        for i, g in enumerate(guess):
            if g != '@' and g in answer:
                answer[answer.index(g)] = '#'
                self._value += 3**i 
      
    @dispatch(int)
    def __init__(self, value: int):
        assert value >= 0, 'Pattern value is smaller than 0'
        self._value = value
        self._words_length = 5

    @dispatch(int, int)
    def __init__(self, value: int, words_len: int):
        assert value >= 0, 'Pattern value is smaller than 0'
        assert words_len > 0, 'Length of words is greater than 0'
        self._value = value
        self._words_length = words_len
    
    @dispatch(str)
    def __init__(self, pattern: str):
        """Pattern can only contain '0' '1' and '2'"""
        for d in pattern:
            assert d in '012', 'pattern can only contain \'0\' \'1\' and \'2\''

            self._value += int(d)
        self._words_length = len(pattern)


    def __str__(self) -> str:
        val = self._value
        result = ''
        while val > 0:
            val, digit = divmod(val, 3)
            match digit:
                case 0: 
                    result += '⬛'
                case 1: 
                    result += '🟨'
                case 2: 
                    result += '🟩'

        while len(result) < self._words_length:
            result += '⬛'
        
        return result

    def __repr__(self) -> str:
        return f'Pattern({self.val})'

    def __eq__(self, other: Pattern) -> bool:
        if not isinstance(other, Pattern):
            raise ValueError(f'Can\'t compare pattern with {type(other)}')
        
        return self._value == other._value