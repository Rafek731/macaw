
class InvalidPatternError(Exception):
    """Exception raised for invalid pattern"""

    def __init__(self, message, error_code):
        super().__init__(message)
        self.error_code = error_code

    def __str__(self):
        return f"{self.message} (Error Code: {self.error_code})"

class FileProcessingError(Exception):
    """Exception raised if any errors during file processing emerge"""
    def __init__(self, message, filename, lineno=None):
        super().__init__(message)
        self.filename = filename
        self.lineno = lineno

    def __str__(self):
        return f"In {self.filename} at line {self.lineno}:\n{self.message}"
