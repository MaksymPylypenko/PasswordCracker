#include <iostream>
#include <thread> 
#include "utility.h"

//bool cracker(std::string hash, std::string& plain) {
//
//	int i, j;
//	int comparisons = 0;
//
//	plain.assign(3, 'a');
//	return true;
//}


int main() {

	std::string mask = "lu";
	std::string word = init(mask);

	std::cout << "Start\n";

	bool wordsLeft = true;
	while (wordsLeft) {
		std::cout << word << "\n";

		if (!inc(word,mask)) {
			wordsLeft = false;
		}
	}
	
    
    return 0;
}