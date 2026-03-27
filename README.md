# Macaw 🦜
One of a kind worlde solver with specifiable target words list!<br>
Inspired by [3b1b video](https://youtu.be/v68zYyaEmEA) on solving wordle using entropy (and my friend playing wordle on lectures). 

## Setup ⚙️
### Linux/MacOs
1. Create virtual environment for python
```bash
python3.x -m venv .venv
source .venv/bin/activate
```
where `x` is your python version

2. Run
```bash
pip3 install -r requirements.txt
python3 setup.py build_ext
pip3 install --no-build-isolation .
```
### Windows
Currently unsupported (work in progress)

>**Note**: you have to have compiler supporting C++23 installed

## What is ***Wordle***? 📝
***Wordle*** is a clever game where you have 6 guesses to guess a 5 letter word out of **~15,000** possible valid words (specified beforehand). After each attempt wordle gives you feedback about which letters you guessed correctly, which are misplaced and which do not occur in the answer

## How ***Wordle*** calcualtes patterns? ⬛🟨🟩
Here is the screen from [official wordle website](https://www.nytimes.com/games/wordle/index.html)

![screen](imgs/Screenshot%20from%202026-03-27%2023-44-08.png)

## Usage of macaw
To run ***macaw*** type:
```bash
python3 main.py /path/to/valid/words/file
```
Original ***wordle*** valid words are in file `words/english_original.txt`<br>

1. Wait for macaw to load the words 
2. Type desired word to ***wordle***
3. Type the same word to ***macaw*** and press Enter
4. Pass wordle generated pattern:
    * If  ⬛ type **0**
    * If  🟨 type **1**
    * If  🟩 type **2**

Example: 🟩⬛⬛🟨🟨 = **2 0 0 1 1**

5. Go to point 2

## How does it work?
First ***macaw*** model is called ***Bule***. It is based on the concept of entropy as inspired by the video mentioned at the beggining.

Though it is not the most optimal way of solcing wordle - it works!


