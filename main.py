#!/usr/bin/env python3
import macaw
import argparse
from time import sleep
import os

def clear_terminal():
    os.system('cls' if os.name == 'nt' else 'clear')


def main(valid_words_path: str) -> None:
    clear_terminal()
    print("Welcome to macaw showcase! Wait as I load needed words.")
    bot = macaw.Blue(valid_words_path)
 
    print('Done!\n')

    while True:
        clear_terminal()
        top = bot.top_guesses(10)

        assert len(top) > 0, "You must have passed an invalid pattern somewhere"

        if len(top) == 1:
            print(f'Your word is \'{top[0][0]}\'!')
            break

        print(f'Best words for now ({len(bot.words())}):')
        
        for i, tup in enumerate(top, start=1):
            print(f'{i}. {tup[0]}: {tup[1]}')
        print()

        user_guess = input('Please enter your guess: ')
        user_pattern = input('What pattern have wordle shown: ')

        bot.guess_made(user_guess, user_pattern)
    input("Press Enter to quit")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Showcase of macaw wordle solver')
    parser.add_argument('valid_words_path', type=str, help='Path to file containing valid words')
    parser.add_help = True

    args = parser.parse_args()
    main(args.valid_words_path)
