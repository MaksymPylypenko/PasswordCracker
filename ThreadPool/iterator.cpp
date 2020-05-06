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


Iterator::Iterator(std::string mask, std::vector<int> offset) {
	this->mask = mask;
	this->offset = offset;
	
	currDigits = 1;
	slowestRotor = 0; // or currDigits - 1
	combinations = std::vector<int>(currDigits, 1);
	maxDigits = mask.size();
}


void Iterator::resetRotors() {

	std::string charset;
	start = mask;
		
	// The total number of combinations is simply:
	// comb at pos 1 * comb at pos 2 * comb at pos 3 ...

	combinations = std::vector<int>(currDigits, 1);
	for (int i = 0; i < currDigits; i++) {
		charset = charsetOf(mask[i]);
		start.at(i) = charset.at(offset[i]);
			
		// Since the initial position of some rotors is not at the start, we have less combinations
				
		combinations[i] = charset.size() - offset[i];
		for (int j = 0; j < i; j++) {	
			// Full rounds
			charset = charsetOf(mask[j]);
			combinations[i] *= charset.size();			
		}		

		int rest = 0;		
		for (int j = 0; j < i; j++) {
			// Short round
			rest += offset[i];			
		}
		combinations[i] -= rest;
	    
		//printf("current combinations = %d\n", combinations[i]);
	}

	word = start.substr(0, currDigits);
	slowestRotor = currDigits - 1;
}



bool Iterator::next(int rotor) {
	//printf("wordsLeft = %d\n", combinations[slowestRotor]);

	if (combinations[slowestRotor] <=1) {
		return false;
	}

	if (rotor >= word.size()) {
		printf("Failed to estimate combinations!\n");
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
	combinations[slowestRotor]--;	
	word.at(rotor)++;
	return true;
}


bool Iterator::guessWord() {
	if (!next()) {		
		currDigits++;
		if(currDigits > maxDigits) {
			return false;
		}
		resetRotors();
	}
	return true;
}