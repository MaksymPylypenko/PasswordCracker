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
	offsetBreak.clear();
	for (char& c : mask) {
		std::string charset = charsetOf(c);
		offsetBreak.push_back(charset.size()-1);
	}


	currDigits = 1;
	slowestRotor = 0; // or currDigits - 1
	rotationsLeft = std::vector<int>(currDigits, 1);
	maxDigits = mask.size();
}


void Iterator::setStart(std::vector<int> offset) {
	offsetStart = offset;
}


void Iterator::setFinish(std::vector<int> offset) {	
	offsetBreak = offset;
}


void Iterator::setWordLen(int n) {
	currDigits = n;
}


void Iterator::debug() {

	printf("Word='");
	int i = 0;
	for (i = 0; i < word.size(); i++) {
		if (i == slowestRotor) {
			printf("[");
		}
		printf("%c", word.at(i));
		if (i == slowestRotor) {
			printf("]");
		}
	}	
	printf("'\t#%d\tRotors=[", count);
	for (i = 0; i < rotationsLeft.size()-1; i++) {
		printf("%d-", rotationsLeft[i]);
	}
	printf("%d]", rotationsLeft[i]);
	printf("\n");
}

bool Iterator::resetRotors() {
	count = 1;

	if (currDigits > maxDigits) {
		return false;
	}

	std::string charset;
	initWord = std::string(mask.size(),' ');

	rotationsLeft = std::vector<int>(currDigits);
	int i=0;
	for (i = 0; i < currDigits; i++) {
		charset = charsetOf(mask[i]);
		initWord.at(i) = charset.at(offsetStart[i]);
			
		// Limit the number of rotations				
		rotationsLeft[i] = offsetBreak[i];
	}

	// The right most rotor might not need a full round!
	int j = i - 1;
	rotationsLeft[j] = offsetBreak[j] - offsetStart[j];

	word = initWord.substr(0, currDigits);
	slowestRotor = currDigits - 1;
	

	return true;
}


bool Iterator::next(int rotor) {
	//printf("wordsLeft = %d\n", rotationsLeft[slowestRotor]);

	if (rotor >= word.size()) {
		// This may happen when a custom [offsetStart] is used. 
		printf("\nAttempted to rotate a rotor that is outside boundaries!\n\n");
		return false;
	}

	if (rotationsLeft[slowestRotor] <= 0) {
		printf("\nRotor [%d] has reached its final position [%c]\n\n", slowestRotor, word[slowestRotor]);
		slowestRotor--; 
		if (slowestRotor == -1) {
			return false;
		}
	}
	
	count++;

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