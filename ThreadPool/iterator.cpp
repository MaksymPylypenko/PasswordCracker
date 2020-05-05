#include "utility.h"

/// Charsets
std::string lowerCase = "abcdefghijklmnopqrstuvwxyz";
std::string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string numbers = "0123456789";
std::string defaultMask = "llllllllllllllllllllllll";


std::string init(std::string mask) {

	std::string out = mask;

	for (char& c : out) {
		if (c == 'u') {
			c = upperCase[0];			
		}
		else if (c == 'l') {
			c = lowerCase[0];
		}
	}	

	return out;
}


/// Recursively iterates all possible combinations
bool inc(std::string& word, std::string& mask, int index) {
		
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
		if (word.at(index) == upperCase.at(upperCase.size()-1)) {
			word.at(index) = upperCase.at(0);
			return inc(word, mask, index + 1); // for 
		}
	}
	else if (mask[index] == 'l') {
		if (word.at(index) == lowerCase.at(lowerCase.size()-1)) {
			word.at(index) = lowerCase.at(0);
			return inc(word, mask, index + 1); // for 
		}
	}	


	word.at(index)++; // iterate ascii
	return true;
}