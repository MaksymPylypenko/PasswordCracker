#include <iostream>
#include <thread> 
#include "utility.h"

void cracker(int id) {

	std::string mask = "ddd";	
	Iterator iterator = Iterator(mask);
	iterator.setStart(std::vector<int>(mask.size(), 5)); 
	iterator.setBreak(std::vector<int>(mask.size(), 7));
	iterator.resetRotors();
		
	bool wordsLeft = true;
	while(wordsLeft) {
		iterator.debug();
		//if (iterator.word == "gg") { // @todo, compute hash and compare to plain-text
		//	std::cout << id << " found\n";
		//	return;
		//}

		wordsLeft = iterator.guessWord();		
	}	
	//iterator.divideWork(4);
}


int main() {

	std::cout << "Program started\n";

	std::thread th1(cracker, 1);	
	th1.join();
    
    return 0;
}