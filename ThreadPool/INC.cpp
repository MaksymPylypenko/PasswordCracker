#include "utility.h"

const int lettersNum = 26;
const int lastLetter = lettersNum-1;
const int numbersNum = 10;
const int lastNumber = numbersNum - 1;

const char lowerCase[lettersNum +1] = "abcdefghijklmnopqrstuvwxyz";
const char upperCase[lettersNum +1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char numbers[lettersNum + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char mask[6] = "lllll";

/// Recursively iterates all possible combinations
bool inc(std::string& word, int index) {
		
	// Reached the end of a word
	if (index >= word.size()) {
		return false;
	}

	// Move to the next index when the round is finished 
	// Example:
	// a a --> b a --> ... --> z a  
	// a b --> b b --> ... --> z b
	// a c --> b c --> ... --> z c
	if (mask[index] == 'u') {
		if (word.at(index) == upperCase[lastLetter]) {
			word.at(index) = upperCase[0];
			return inc(word, index + 1); // for 
		}
	}
	else if (mask[index] == 'l') {
		if (word.at(index) == lowerCase[lastLetter]) {
			word.at(index) = lowerCase[0];
			return inc(word, index + 1); // for 
		}
	}	


	word.at(index)++; // iterate ascii
	return true;
}