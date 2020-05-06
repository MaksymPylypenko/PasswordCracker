#include <iostream>
#include <thread> 
#include "utility.h"

void cracker(int id) {


	std::string mask = "ll";
	std::vector<int> offset{ 0,0 };

	Iterator iterator = Iterator(mask);
	iterator.init(offset);


	for (int digits = 1; digits <= mask.size(); digits++) {
		iterator.setLen(digits);

		printf("\nInitial word = %s \n", iterator.word.c_str()); 
		printf("Expected combinations %d\n\n", iterator.combinations[iterator.id]);

		bool wordsLeft = true;
		while (wordsLeft) {

			if (iterator.word == "gg") { // @TODO, compute hash and compare to plain-text
				std::cout << id << " found\n";
				return;
			}

			printf("current word = %s \n", iterator.word.c_str());

			if (!iterator.next()) {
				wordsLeft = false;
			}
		}			
		
	}	
}


int main() {

	std::cout << "Program started\n";

	std::thread th1(cracker, 1);	
	th1.join();
    
    return 0;
}