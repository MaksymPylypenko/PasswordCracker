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


void Iterator::setBreak(std::vector<int> offset) {	
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

	if (rotor >= word.size()) {
		assert(false && "Rotation outside bounds");
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


std::vector<Iterator> Iterator::divideWork(int N) {

	std::vector<Iterator> jobs;

	// 1. Find total work

	std::vector<int> totalWork;
	std::vector<int> smallWork;

	for (char& c : mask) {
		std::string charset = charsetOf(c);
		totalWork.push_back(charset.size());
	}

	// 2. Find offsets

	smallWork = totalWork;

	for (int& i : smallWork) {
		i = i / N;
	}
	
	std::vector<int> prev(mask.size(), 0);
	int range = 0;
	for (range = 0; range < N-1; range++) {
		// 0 to work
		// work to work+work
		// prev to prev+work
		std::vector<int> start = prev;



		std::vector<int> end = start;
		for (int rotor = 0; rotor < mask.size(); rotor++) {
			end[rotor] += smallWork[rotor];
		}
		prev = end;

		printf("\n\nStart ");
		for (int& i : start) {
			printf("%d,", i);
		}
		printf("\nEnd ");
		for (int& i : end) {
			printf("%d,", i);
		}
	}

	// Dealing with odd [N]
	std::vector<int> start = prev;
	std::vector<int> end = totalWork;

	printf("\n\nStart ");
	for (int& i : start) {
		printf("%d,", i);
	}
	printf("\nEnd ");
	for (int& i : end) {
		printf("%d,", i);
	}


	// 3. Create N iterators

	
	//for (int i = 0; i < N; i++) {
	//	//TODO
	//}
	return jobs;
}