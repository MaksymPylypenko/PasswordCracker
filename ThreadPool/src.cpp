#include <iostream>
#include <thread> 
#include "utility.h"

void cracker(int id) {

	std::string mask = "dd";	
	Iterator iterator = Iterator(mask);
	iterator.setStart(std::vector<int>(mask.size(), 5)); 
	iterator.setFinish(std::vector<int>(mask.size(), 7));
	iterator.resetRotors();
		
	bool wordsLeft = true;
	while(wordsLeft) {
		iterator.debug();
		//printf("%s\n", iterator.word.c_str());

		//if (iterator.word == "gg") { // @todo, compute hash and compare to plain-text
		//	std::cout << id << " found\n";
		//	return;
		//}

		wordsLeft = iterator.guessWord();		
	}	
	//printf("Output = %s\n", iterator.word.c_str());
}


int main() {

	std::cout << "Program started\n";

	std::thread th1(cracker, 1);	
	th1.join();
    
    return 0;
}