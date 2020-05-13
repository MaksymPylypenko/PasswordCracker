#include "iterator.h"

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


bool Rotors::next(int rotor) {

	assert(rotor < digits && "Rotation outside bounds");

	if (rotationsLeft[head] <= 0) {
		//printf("\nRotor [%d] has reached its final position [%c]\n\n", head, word[head]);
		head--;
		if (head == -1) {
			return false;
		}
	}

	// Move to the slower [rotor] when the round is finished.
	// For example:
	// [0][0] --> [1][0] --> ... --> [9][0] 
	// [0][1] --> [1][1] --> ... --> [9][1]
	// [0][2] --> [1][2] --> ... --> [9][2]

	if (curValues[rotor] == maxValues[rotor]) {
		curValues[rotor] = 0;
		return next(rotor + 1);
	}
	if (rotor == head) {
		rotationsLeft[rotor]--;
	}
	curValues.at(rotor)++;
	return true;
}


Rotors::Rotors(std::vector<int> maxValues) {
	this->maxValues = maxValues;
	this->digits = maxValues.size();
	this->head = digits - 1;
}

void Rotors::init() {	
	curValues = std::vector<int>(digits, 0);
	rotationsLeft = maxValues;
}

bool Rotors::initRange(std::vector<int> offsetStart, std::vector<int> offsetBreak) {	
	curValues = std::vector<int>(digits);
	rotationsLeft = std::vector<int>(digits);
	
	// check for impossible range
	if (offsetBreak[head] < offsetStart[head]) {
		// not possible			
		return false;
	}


	int i = 0;
	for (i = 0; i < digits; i++) {
		curValues[i] = offsetStart[i];
		// Limit the number of rotations				
		rotationsLeft[i] = offsetBreak[i];
	}
	// The right most rotor might not need a full round!
	int j = i - 1;
	rotationsLeft[j] = offsetBreak[j] - offsetStart[j];
	return true;
}


std::vector<Rotors> Rotors::slice(int N) {

	std::vector<Rotors> slices;

	// 1. Find the smallest unit of work that a single thread can do.
	std::vector<int> smallWork;
	smallWork = maxValues;
	float carryover = 0.0;
	for (int i = digits - 1; i >= 0; i--) {

		int& rotorValue = smallWork[i];

		// Adding + 1 to show the number of elements at a current rotor, instead of the max offset
		float t = carryover * (maxValues[i] + 1);
		float trueValue = ((float)rotorValue) / N + t;
		rotorValue = (int)trueValue;
		carryover = trueValue - rotorValue;

		//printf("carryover = %f\n", carryover);
		//printf("true value = %f\n", trueValue);
		//printf("rotor value = [%d/%d]\n\n", rotorValue, maxWork);
	}

	// 2. Make ranges using the smallest unit of work.
	std::vector<int> prev(digits, 0);
	int range = 0;
	for (range = 0; range < N; range++) {
		std::vector<int> start = prev;
		int rotor = 0;

		if (range > 0) {
			// start position is not iclusive
			start[rotor] += 1;
			while (start[rotor] > maxValues[rotor]) {
				//overflow
				start[rotor] -= maxValues[rotor] + 1;
				start[rotor + (uint64_t)1]++;
				rotor++;
				assert(rotor < wordlen.size());
			}
		}
		std::vector<int> end = start;
		if (range < N - 1) {
			for (rotor = 0; rotor < digits; rotor++) {
				end[rotor] += smallWork[rotor];

				if (end[rotor] > maxValues[rotor]) {
					//overflow
					end[rotor] -= maxValues[rotor] + 1;
					end[rotor + (uint64_t)1]++;
				}
			}
			prev = end;
		}
		else {
			// Note, it is not always possible to equally divide the work.
			// The last range may be a little bit longer (up to N-1 units).
			end = maxValues;
		}

		Rotors r = Rotors(maxValues);
		r.initRange(start, end);
		slices.push_back(r);
	}
	return slices;
}


//////

void Iterator::updateWord() {
	std::vector<int> values = sets[currSet].curValues;
	word = std::string(values.size(),' ');
	for (int i = 0; i < values.size(); i++) {
		std::string charset = charsetOf(mask[i]);
		word.at(i) = charset.at(values[i]);	
	}
}


Iterator::Iterator(std::string mask) {
	this->mask = mask;
	this->currSet = 0;
}


void Iterator::init() {
	int n = mask.size();
	std::vector<int> maxValues(n);

	// This only works if every digit at [offsetStart] is smaller than every digit at [offsetBreak]
	for (int i = 0; i < n; i++) {
		std::string charset = charsetOf(mask[i]);
		maxValues[i] = charset.size() - 1;
	}

	for (int i = 1; i <= n; i++) {
		std::vector<int> subset(maxValues.begin(), maxValues.begin() + i);
		Rotors r = Rotors(subset);
		r.init();
		sets.push_back(r);
	}
	updateWord();
}


void Iterator::initCustom(std::vector<Rotors> sets) {
	this->sets = sets;
	updateWord();
}


bool Iterator::guessWord() {
	if (!sets[currSet].next()) {		
		currSet++;
		if (currSet < sets.size()) {
			return guessWord();
		}
		else {
			return false;
		}		
	}
	count++;
	updateWord();
	return true;
}


std::vector<Iterator> Iterator::divideWork(int N) {

	std::vector<Iterator> jobs;
	int s = mask.size();
	std::vector<int> maxValues(s);

	for (int i = 0; i < s; i++) {
		std::string charset = charsetOf(mask[i]);
		maxValues[i] = charset.size() - 1;
	}

	std::vector<std::vector<Rotors>> stacks(N);
	// Stacks look like this:
	// [0]-->[2]
	// [0][0]-->[2][2]
	// [0][0]-->[2][2][2]
	// ...

	for (int wordlen = 1; wordlen <= s; wordlen++) {
		std::vector<int> maxWork(maxValues.begin(), maxValues.begin() + wordlen);
		Rotors r = Rotors(maxWork);

		// Slices for [wordlen=1] look like this
		// [0]-->[2], [3]-->[5], [6]-->[8] ...
		// 
		// Similarly for [wordlen=2]:
		// [0][0]-->[2][2], [3][3]-->[5][5] ...
		//
		// This is also for [wordlen=2], but for shorter slices:
		// [0][0]-->[7][1], [8][1]-->[5][3] ...

		std::vector<Rotors> slices = r.slice(N);

		for (int i = 0; i < N; i++) {
			stacks[i].push_back(slices[i]);
		}
	}

	for (int i = 0; i < stacks.size(); i++) { 
		Iterator job = Iterator(mask);
		job.initCustom(stacks[i]);
		jobs.push_back(job);

		/*printf("\nThread %d\n", i);
		for (Rotors r : stacks[i]) {
			std::vector<int> values = r.curValues;
			printf("");
			for (int j : values) {
				printf("[%d]", j);
			}
			printf("\n");
		}*/
	}

	return jobs;
}

// Utility

void Iterator::debug() {
	Rotors curr = sets[currSet];

	printf("Word='");
	int i = 0;
	for (i = 0; i < word.size(); i++) {
		if (i == curr.head) {
			printf("[");
		}
		printf("%c", word.at(i));
		if (i == curr.head) {
			printf("]");
		}
	}
	printf("'\t#%d\tRotors=[", count);
	for (i = 0; i < curr.rotationsLeft.size() - 1; i++) {
		printf("%d-", curr.rotationsLeft[i]);
	}
	printf("%d]", curr.rotationsLeft[i]);
	printf("\n");
}


void printRange(std::vector<int> start, std::vector<int> end) {
	printf("");
	for (int i : start) {	
		printf("[%d]", i);
	}
	printf(" --> ");
	for (int i : end) {
		printf("[%d]", i);
	}
	printf("\n");
}