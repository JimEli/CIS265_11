# Pima CC CIS265 Week #11 Project

Write a program that prompts a user for a number and then displays the number using characters to simulate the effect of a seven-segment 
display.
```Text
  Enter a number : 491 - 9014
       _       _   _
  |_| |_|   | |_| | |   | |_|
    |  _|   |  _| |_|   |   |
```
Characters other than digits should be ignored. Write the program so that the maximum number of digits is controlled by a macro named MAX_DIGITS, which has the value 10. If the number contains more than this number of digits, the extra digits are ignored. 

## Hints:

Use two external arrays. One is the segments array(see Exercise 6 in chapter 8), which stores data representing the correspondence between digits and segments. The outer array, digits, will be an array of characters with 4 rows(since each segmented digit is four characters high) and MAXDIGITS * 4 columns (digits are three characters wide, but a space is needed between digits for readability). 

Write your program as four functions, main, clear_digits_array, process_digit, and print_digits_array.Here are the prototypes for the latter three functions:
```C
  void clear_digits_array(void);
  void process_digit(int digit, int postion);
  void print_digits_array(void);
```
* _clear_digits_array_ will store blank characters into all elements of the digits array. 
* _process_digit_ will store the seven-segment representation of digit into a specified position in the digits array(positions range from 0 to MAX_DIGITS – 1). 
* _print_digits_array_ will display the rows of the digits array, each on a single line, producing output such as that shown in the example.
