# Picos Fermi Bagels 猜数字游戏
## 1. 游戏规则
在 Pico Fermi Bagels 这个逻辑推理游戏中，你要根据线索猜出一个三位数。</br>
游戏会根据你的猜测给出以下提示之一：

1. 如果你猜对一位数字但数字位置不对，则会提示“Pico”
2. 如果你同时猜对了一位数字及其位置，则会提示“Fermi”
3. 如果你猜测的数字及其位置都不对，则会提示“Bagels”。

你有 10 次猜数字机会。

## 2. 运行示例
```cmd
% picos
Bagels, a deductive logic game.
By Al Sweigart al@inventwithpython.com
I am thinking of a 3-digit number. Try to guess what it is.
Here are some clues:
    When I say:     That means:
    Pico            One digit is correct but in the wrong position.
    Fermi           One digit is correct and in the right position.
    Bagels          No digit is correct.
I have thought up a number.
You have 10 guesses to get it.
Guess #1:
> 123
Pico
Guess #2:
> 456
Bagels
Guess #3:
> 178
Pico Pico
--snip--
Guess #7:
> 791
Fermi Fermi
Guess #8:
> 701
You got it!
Do you want to play again? (yes or no)
> no
Thanks for playing!
```