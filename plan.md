## Pattern
- holds patterns as values in trinary system

## Word
- inherits from string
- (Word & Word) <- make pattern

## How call should look like

```python
bot = macaw.macawV1()
bot.set_words_path('/path/to/words')
if not bot.check_precalculated():
    bot.calc()

print(bot.top10())

while True:
    guess = input()
    pattern = int(input(), base=3)
    bot.narrow(guess, pattern)
    bot.top10()

```
## Macaw V1
### Algorithm
Lets say we have loaded words list: word0, word1, word2, ...
for each word we calculate patterns distribution

|       | word0 | word1 | word2 |... ||
|-------|-------|-------|-------|----|-|
| word0 |pat(0,0)|pat(0,1)|pat(0,2)|...| -> dist = [0,52,67,...,9] -> entropy
| word1 |pat(1,0)|pat(1,1)|pat(1,2)|...| -> dist = [5,2,69,...,9] -> entropy
| word2 |pat(2,0)|pat(2,1)|pat(2,2)|...| -> dist = [420,2137,6,...,9] -> entropy
|...|||||

So we'll need to implement
- pattern making
- distribution counting
- entropy

### Pattern making
1. Find perfect matches
2. Find semi matches from lef to right