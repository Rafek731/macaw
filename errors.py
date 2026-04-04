
class InvalidPatternError(Exception):
    """Exception raised for invalid pattern"""

    def __init__(self, message):
        super().__init__(message)

class FileProcessingError(Exception):
    """Exception raised if any errors during file processing emerge"""
    def __init__(self, message, filename, lineno=None):
        super().__init__(message)
        self.filename = filename
        self.lineno = lineno

    def __str__(self):
        return f"In {self.filename} at line {self.lineno}:\n{self.message}"
    
class WordError(Exception):
    """Exception related to words given by user"""
    def __init__(self, message):
        super().__init__(message)
