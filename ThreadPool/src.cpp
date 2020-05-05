#include <iostream>
#include <thread> 
#include "utility.h"

bool cracker() {

	int comparisons = 0;

	std::string mask = "llll";
	std::string plain = init(mask);
	std::string word;

	for (int end = 1; end <= mask.size(); end++) {
		word = plain.substr(0, end);

		bool wordsLeft = true;
		while (wordsLeft) {

			if (word == "gggg") { // @TODO, add a hash function here...
				std::cout << "Found\n";
				return true;
			}

			std::cout << word << "\n";

			if (!inc(word, mask)) {
				wordsLeft = false;
			}
		}			
		
	}	
	return false;
}


int main() {

	std::string mask = "lu";
	std::string word = init(mask);

	std::cout << "Start\n";

	cracker();
	
    
    return 0;
}