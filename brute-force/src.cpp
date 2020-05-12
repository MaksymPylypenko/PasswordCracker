#include <iostream>
#include <thread> 
#include "iterator.h"
#include "comparator.h"

// Shared variables
bool match = false;

void cracker(Iterator &iterator, std::string digest, int id) {		
	bool wordsLeft = true;
	while(wordsLeft && !match) {
		//iterator.debug();
		if (isMatch(iterator.word, digest)) {
			std::cout << "Thread (" << id << ") found a match = [" << iterator.word << "]\n";
			match = true;
			return;
		}
		wordsLeft = iterator.guessWord();		
	}	
}

int main() {

	std::cout << "Program started\n";

	std::string hex = "69d08b4e9c06fb98e1b42192348d258ec8397f3c3da2971605c8335224999736";
	std::string digest = getBytes(hex);

	std::string mask = "lllll";
	Iterator iterator = Iterator(mask);

	std::vector<Iterator> jobs = iterator.divideWork(4);	
	std::vector<std::thread> threads(jobs.size());
	
	int threadID = 0;
	for (Iterator & iter : jobs) {
		std::thread th(cracker, std::ref(iter), digest, threadID++);
		threads.push_back(move(th));
	}
	for (std :: thread & th : threads) {
		if (th.joinable())
			th.join();
	}
    
    return 0;
}