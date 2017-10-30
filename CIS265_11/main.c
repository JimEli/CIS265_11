/*************************************************************************
* Title: (CIS265_11) 7-Segment Display
* File: main.c
* Author: James Eli
* Date: 9/2/2017
*
* Write a program that prompts a user for a number and then displays the 
* number using characters to simulate the effect of a seven-segment 
* display.
*   Enter a number : 491 - 9014
*        _       _   _
*   |_| |_|   | |_| | |   | |_|
*     |  _|   |  _| |_|   |   |
*
* Characters other than digits should be ignored. Write the program so that 
* the maximum number of digits is controlled by a macro named MAX_DIGITS, 
* which has the value 10. If the number contains more than this number of 
* digits, the extra digits are ignored. Hints: Use two external arrays. One 
* is the segments array(see Exercise 6 in chapter 8), which stores data 
* representing the correspondence between digits and segments. The outer 
* array, digits, will be an array of characters with 4 rows(since each 
* segmented digit is four characters high) and MAXDIGITS * 4 columns (digits 
* are three characters wide, but a space is needed between digits for 
* readability). Write your program as four functions, main, clear_digits_array, 
* process_digit, and print_digits_array.Here are the prototypes for the latter 
* three functions:
*   void clear_digits_array(void);
*   void process_digit(int digit, int postion);
*   void print_digits_array(void);
* clear_digits_array will store blank characters into all elements of the 
* digits array. process_digit will store the seven-segment representation of 
* digit into a specified position in the digits array(positions range from 0 
* to MAX_DIGITS – 1). print_digits_array will display the rows of the digits 
* array, each on a single line, producing output such as that shown in the 
* example.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/02/2017: Initial release. JME
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIGITS 10 // Maximum digits for entry/display.

// Holds characters for 7-segment display of entered digits.
char digits[3][(MAX_DIGITS * 4) + 1];

// Store 7-segment characterization of a digit (0-9).
void process_digit(int digit, int position) {
	/*
	   Defines which 7-segment(s) of digit are displayed (0==off, 1==on). 
	   Encoded as (MSB to LSB): (1) top-left segment, (2) top horizontal, (3) top-right, (4) space, 
	   (5) left-middle vertical, (6) middle horizontal, (7) right-middle vertical, (8) space, 
	   (9) left-bottom vertical, (10) bottom horizontal, (11) right-bottom vertical, (12) space.
	   The 7-segments are defined by the x bits: 0b0x00xxx0xxx0.
	*/
	unsigned short int segments[10] = {
		0b0100'1010'1110, // 0
		0b0000'0010'0010, // 1
		0b0100'0110'1100, // 2
		0b0100'0110'0110, // 3
		0b0000'1110'0010, // 4
		0b0100'1100'0110, // 5
		0b0100'1100'1110, // 6
		0b0100'0010'0010, // 7
		0b0100'1110'1110, // 8
		0b0100'1110'0110  // 9 
	};
	// Characters representing the individual segments.
	char segmentCharacters[4] = { '|', '_', '|', ' ' };
	// Bit used to index the correct segment character.
	unsigned short int bit = 0b1000'0000'0000;

	// Store segment characters into digits array.
	for (int i = 0; i < 4; i++, bit >>= 1) {
		digits[0][position * 4 + i] = (segments[digit] & bit) ? segmentCharacters[i] : ' ';      // Top row.
		digits[1][position * 4 + i] = (segments[digit] & bit >> 4) ? segmentCharacters[i] : ' '; // Middle row.
		digits[2][position * 4 + i] = (segments[digit] & bit >> 8) ? segmentCharacters[i] : ' '; // Bottom row.
	}
}

// Completely clear digit array.
void clear_digits_array(void) {
	memset(digits, 0, sizeof(digits[0][0]) * sizeof(char) * ((MAX_DIGITS * 4) + 1) * 3);
}

// Iterate digit array printing it.
void print_digits_array(void) {
	for (int i = 0; i < 3; fprintf(stdout, "%s\n", digits[i++])); 
	fputs("\n", stdout);
}

// Program starts here.
int main(void) {
	char number[MAX_DIGITS + 2]; // Holds user entered numbers (LF and terminator).

	// Enter number.
	fputs("Enter an integer number (up to 10 digits): ", stdout);
	if (!fgets(number, sizeof number, stdin)) {
		fputs("Fatal program error!\n", stderr);
		exit(EXIT_FAILURE);
	}
	else if (!strchr(number, '\n')) {
		// Input too long, eat remainder.
		while (fgets(number, sizeof number, stdin) && !strchr(number, '\n'))
			; // Empty body.
		fputs("Too many characters input.\n", stdout);
	}
	else {
		unsigned int i = 0, j = 0; // Separate array indicies.

		clear_digits_array();

		// Iterate through input, checking for digits and process accordingly.
		while (i < strlen(number) && j < MAX_DIGITS) {
			if (isdigit(number[i])) 
				process_digit(number[i] - '0', j++);
			i++;
		}

		// Display the number simulating a 7-segment display.
		print_digits_array();
	}
}
