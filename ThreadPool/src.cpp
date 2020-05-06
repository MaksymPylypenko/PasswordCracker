#include <iostream>
#include <thread> 
#include "utility.h"

void cracker(int id) {


	std::string mask = "ll";
	std::vector<int> offset(2,0);

	Iterator iterator = Iterator(mask,offset);
	iterator.resetRotors();
		
	bool wordsLeft = true;

	//printf("\nInitial word = %s \n", iterator.word.c_str());
	//printf("Expected combinations %d\n\n", iterator.combinations[iterator.slowestRotor]);

	while(wordsLeft) {
		printf("current word = %s \n", iterator.word.c_str());

		if (iterator.word == "gg") { // @TODO, compute hash and compare to plain-text
			std::cout << id << " found\n";
			return;
		}
		wordsLeft = iterator.guessWord();		
	}	
}


int main() {

	std::cout << "Program started\n";

	std::thread th1(cracker, 1);	
	th1.join();
    
    return 0;
}