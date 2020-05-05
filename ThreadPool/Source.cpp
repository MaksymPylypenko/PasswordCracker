#include <iostream>
#include "utility.h"


int main() {
    std::string word = "aa";

	std::cout << "Start\n";

	bool wordsLeft = true;
	while (wordsLeft) {
		std::cout << word << "\n";

		if (!inc(word)) {
			wordsLeft = false;
		}
	}
	
    
    return 0;
}