#include "utility.h"

/// Charsets
std::string lowerCase = "abcdefghijklmnopqrstuvwxyz";
std::string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string numbers = "0123456789";
std::string defaultMask = "llllllllllllllllllllllll";


std::string charsetOf(char type) {
	switch (type) {
	case 'u':
		return upperCase;
		break;
	case 'l':
		return lowerCase;
		break;	
	}
}


Iterator::Iterator(std::string mask) {
	this->mask = mask;
	combinations = std::vector<int>(mask.size(),0);
}


void Iterator::init(std::vector<int> offset) {

	std::string charset;
	start = mask;
	int n = mask.size();

	// The total number of combinations is simply:
	// comb at pos 1 * comb at pos 2 * comb at pos 3 ...

	for (int i = 0; i < n; i++) {
		charset = charsetOf(mask[i]);
		start.at(i) = charset.at(offset[i]);

		// Since the initial position of some rotors is not at the start, we have less combinations
		combinations[i] = charset.size() - offset[i];

		for (int j = 0; j < i; j++) {
			combinations[i] *= combinations[j];
		}		
	}
}


void Iterator::setLen(int digits) {
	word = start.substr(0, digits);
	id = digits-1; // -1, since I am using it as an index for [capacities]
}


bool Iterator::next(int rotor) {
	if (combinations[id] <=1) {
		return false;
	}

	// Move to the next [rotor] when the round is finished 
	// Example:
	// [a][a] --> [b][a] --> ... --> [z][a] 
	// [a][b] --> [b][b] --> ... --> [z][b]
	// [a][c] --> [b][c] --> ... --> [z][c]

	std::string charset = charsetOf(mask[rotor]);
	int first = 0;
	int last = charset.size() - 1;
	if (word.at(rotor) == charset.at(last)) {
		word.at(rotor) = charset.at(first);
		return next(rotor+1);
	}
	combinations[id]--;
	word.at(rotor)++;
	return true;
}