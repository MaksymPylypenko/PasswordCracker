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
	case 'd':
		return numbers;
		break;
	}
}


Iterator::Iterator(std::string mask) {
	this->mask = mask;
	offsetStart = std::vector<int>(mask.size(), 0);	

	for (char& c : mask) {
		std::string charset = charsetOf(c);
		offsetBreak.push_back(charset.size());
	}

	currDigits = 1;
	slowestRotor = 0; // or currDigits - 1
	rotationsLeft = std::vector<int>(currDigits, 1);
	maxDigits = mask.size();
}


bool Iterator::resetRotors() {
	if (currDigits > maxDigits) {
		return false;
	}

	std::string charset;
	initWord = std::string(mask.size(),' ');

	rotationsLeft = std::vector<int>(currDigits);
	for (int i = 0; i < currDigits; i++) {
		charset = charsetOf(mask[i]);
		initWord.at(i) = charset.at(offsetStart[i]);
			
		// Limit the number of rotations				
		rotationsLeft[i] = offsetBreak[i]; // -offsetStart[i];
	}

	word = initWord.substr(0, currDigits);
	slowestRotor = currDigits - 1;

	return true;
}



bool Iterator::next(int rotor) {
	//printf("wordsLeft = %d\n", rotationsLeft[slowestRotor]);

	//printf("Rotations at %d = %d\n", rotor, rotationsLeft[rotor]);

	if (rotationsLeft[slowestRotor] <= 1) {
		//printf("Rotor [%d] has reached its final position [%c]\n", slowestRotor, word[slowestRotor]);
		slowestRotor--; 
		if (slowestRotor == -1) {
			//printf(" All rotors have reached their final positions!\n");
			return false;
		}
	}
	
	if (rotor >= word.size()) {
		// This happens when a custom [offsetStart] is used. 
		//printf("Attempted to rotate a rotor that is outside boundaries!\n");
		return false;
	}

	// Move to the slower [rotor] when the round is finished.
	// For example:
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

	if (rotor == slowestRotor) {
		rotationsLeft[rotor]--;
	}
	
	word.at(rotor)++;
	return true;
}


bool Iterator::guessWord() {
	if (!next()) {	
		currDigits++;
		return resetRotors();
	}
	return true;
}

std::vector<Iterator> divideWork(int N) {

	std::vector<Iterator> jobs;

	// 1. Find total work
	// 2. Find offsets
	// 3. Create N iterators

	for (int i = 0; i < N; i++) {
		//TODO
	}
	return jobs;
}