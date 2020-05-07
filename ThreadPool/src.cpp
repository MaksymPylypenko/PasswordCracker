#include <iostream>
#include <thread> 
#include "utility.h"

void cracker(int id) {

	std::string mask = "dd";	
	Iterator iterator = Iterator(mask);
	iterator.offsetStart = std::vector<int>(mask.size(), 5); // start at [c][c]
	iterator.offsetBreak = std::vector<int>(mask.size(), 7); // finish at [e][e] 
	iterator.resetRotors();
		
	bool wordsLeft = true;
	while(wordsLeft) {
		printf("%s\n", iterator.word.c_str());

		//if (iterator.word == "gg") { // @todo, compute hash and compare to plain-text
		//	std::cout << id << " found\n";
		//	return;
		//}

		wordsLeft = iterator.guessWord();		
	}	
}


int main() {

	std::cout << "Program started\n";

	std::thread th1(cracker, 1);	
	th1.join();
    
    return 0;
}