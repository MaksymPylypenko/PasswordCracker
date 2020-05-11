#include <iostream>
#include <thread> 
#include "utility.h"

// Shared variables
bool match = false;

void cracker(Iterator &iterator, int id) {		
	bool wordsLeft = true;
	while(wordsLeft && !match) {
		//iterator.debug();
		if (iterator.word == "gggg") { // @todo, compute hash and compare to plain-text
			std::cout << "Thread (" << id << ") found a match = [" << iterator.word << "]\n";
			match = true;
			return;
		}
		wordsLeft = iterator.guessWord();		
	}	
}

int main() {

	std::cout << "Program started\n";

	std::string mask = "llll";
	Iterator iterator = Iterator(mask);

	std::vector<Iterator> jobs = iterator.divideWork(4);	
	std::vector<std::thread> threads(jobs.size());
	
	//std::thread th(cracker, std::ref(jobs[0]));
	//th.join();

	int threadID = 0;
	for (Iterator & iter : jobs) {
		std::thread th(cracker, std::ref(iter), threadID++);
		threads.push_back(move(th));
	}
	for (std :: thread & th : threads) {
		if (th.joinable())
			th.join();
	}
    
    return 0;
}