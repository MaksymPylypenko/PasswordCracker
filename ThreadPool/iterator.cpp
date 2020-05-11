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
	offsetFinish.clear();
	for (char& c : mask) {
		std::string charset = charsetOf(c);
		offsetFinish.push_back(charset.size()-1);
	}

	count = 1;
	currDigits = 1;
	slowestRotor = 0; // or currDigits - 1
	rotationsLeft = std::vector<int>(currDigits, 1);
	maxDigits = mask.size();
}


Iterator::Iterator(std::string mask, std::vector<int> offsetStart, std::vector<int> offsetFinish) {
	this->mask = mask;
	this->offsetStart = offsetStart;
	this->offsetFinish = offsetFinish;
	count = 1;
	currDigits = 1;
	maxDigits = mask.size();
	resetRotors(); 
}


void Iterator::setStart(std::vector<int> offset) {
	offsetStart = offset;
}


void Iterator::setFinish(std::vector<int> offset) {	
	offsetFinish = offset;
}


void Iterator::setWordLen(int n) {
	currDigits = n;
}


bool Iterator::resetRotors() {

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
		rotationsLeft[i] = offsetFinish[i];
	}

	// The right most rotor might not need a full round!
	int j = i - 1;
	rotationsLeft[j] = offsetFinish[j] - offsetStart[j];

	word = initWord.substr(0, currDigits);
	slowestRotor = currDigits - 1;
	

	return true;
}


bool Iterator::next(int rotor) {
	
	assert(rotor < word.size() && "Rotation outside bounds");

	if (rotationsLeft[slowestRotor] <= 0) {
		//printf("\nRotor [%d] has reached its final position [%c]\n\n", slowestRotor, word[slowestRotor]);
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
		count++;
		currDigits++;
		return resetRotors();
	}
	return true;
}


std::vector<Iterator> Iterator::divideWork(int N) {
	std::vector<Iterator> jobs;

	// 1. Find total work
	std::vector<int> maxWork;
	for (char& c : mask) {
		std::string charset = charsetOf(c);
		maxWork.push_back(charset.size()-1);
	}

	// 2. Find the smallest unit of work that a single thread can do.
	std::vector<int> smallWork;
	smallWork = maxWork;
	float carryover = 0.0; 
	for (int i = smallWork.size()-1; i >=0 ; i--) {
		
		int& rotorValue = smallWork[i];
		int& maxValue = maxWork[i];

		// Adding + 1 to show the number of elements at a current rotor, instead of the max offset
		float t = carryover * (maxValue+1); 
		float trueValue = ((float)rotorValue) / N + t;
		rotorValue = (int)trueValue;				
		carryover = trueValue-rotorValue;		

		//printf("carryover = %f\n", carryover);
		//printf("true value = %f\n", trueValue);
		//printf("rotor value = [%d/%d]\n\n", rotorValue, maxValue);
	}	

	// 3. Make ranges using the smallest unit of work.
	std::vector<int> prev(mask.size(), 0);
	int range = 0;
	for (range = 0; range < N; range++) {		
		std::vector<int> start = prev;
		int rotor = 0;

		if (range > 0) {
			// start position is not iclusive
			start[rotor] += 1;
			while (start[rotor] > maxWork[rotor]) {
				//overflow
				start[rotor] -= maxWork[rotor]+1;
				start[rotor + (uint64_t)1]++;
				rotor++;
				assert(rotor < mask.size());
			}
		}
		std::vector<int> end = start;
		if (range < N - 1) {			
			for (rotor = 0; rotor < mask.size(); rotor++) {
				end[rotor] += smallWork[rotor];

				if (end[rotor] > maxWork[rotor]) {
					//overflow
					end[rotor] -= maxWork[rotor]+1;
					end[rotor + (uint64_t)1]++;
				}
			}
			prev = end;
		}
		else {
			// Note, it is not always possible to equally divide the work.
			// The last range may be a little bit longer (up to N-1 units).
			end = maxWork;
		}	
		Iterator job = Iterator(mask, start, end);
		job.printRange();
		jobs.push_back(job);
	}
	return jobs;
}


// Utility

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
	for (i = 0; i < rotationsLeft.size() - 1; i++) {
		printf("%d-", rotationsLeft[i]);
	}
	printf("%d]", rotationsLeft[i]);
	printf("\n");
}


void Iterator::printRange() {
	printf("");
	for (int& i : offsetStart) {
		printf("[%d]", i);
	}
	printf("\t-->\t");
	for (int& i : offsetFinish) {
		printf("[%d]", i);
	}
	printf("\n");
}