#!/usr/bin/env python3
import macaw
import argparse
import subprocess
from time import sleep

def clear_terminal():
    print("\033[H\033[2J", end="")


def main(valid_words_path: str) -> None:
    clear_terminal()
    print("Welcome to macaw showcase! Wait as I load needed words.")
    bot = macaw.Blue(valid_words_path)
 
    print('Done!\n')
    sleep(0.2)

    while True:
        clear_terminal()
        top = bot.top_guesses(10)

        assert len(top) > 0, "You must have passed an invalid pattern somewhere"

        if len(top) == 1:
            print(f'Your word is \'{top[0][0]}\'!')
            break

        print(f'Best words for now ({len(top)}):')
        
        for i, tup in enumerate(top):
            print(f'{i}. {tup[0]}: {tup[1]}')
        print()

        user_guess = input('Please enter your guess: ')
        user_pattern = input('What pattern have wordle shown: ')

        bot.guess_made(user_guess, user_pattern)


    



if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Showcase of macaw wordle solver')
    parser.add_argument('valid_words_path', type=str, help='Pass path to file containing valid words')
    args = parser.parse_args()
    main(args.valid_words_path)

    

