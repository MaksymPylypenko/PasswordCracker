#include <iostream>
#include <thread> 
#include "iterator.h"
#include "comparator.h"
#include <mutex>   
#include <chrono>


// Shared variables
bool match = false;
std::mutex printLock;

std::chrono::time_point<std::chrono::high_resolution_clock> start;
std::chrono::time_point<std::chrono::high_resolution_clock> finish;


void cracker(Iterator &iterator, std::string digest, int id) {		
	bool wordsLeft = true;
	while(wordsLeft && !match) {
		//iterator.debug();
		if (isMatch(iterator.word, digest)) {
			std::cout << "Thread (" << id << ") found a match = [" << iterator.word << "]\n";
			finish = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start;
			std::cout << "Elapsed time: " << elapsed.count() << " s\n";
			match = true;
			return;
		}
		wordsLeft = iterator.guessWord();		
	}	
	printLock.lock();
	std::cout << "Thread (" << id << ") joined\n";
	//printf("wordsLeft ? %s\n", wordsLeft ? "true" : "false");
	printLock.unlock();
}


void spinner() {
	static char bars[] = { '/', '-', '\\', '|' };
	static int nbars = sizeof(bars) / sizeof(char);
	static int pos = 0;

	printf("%c\b", bars[pos]);
	//fflush(stdout);
	pos = (pos + 1) % nbars;
}


int main() {

	std::cout << "Program started\n";

	std::string hex = "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824";
	//std::cout << "Enter a SHA-256 hash (hex format): ";
	//std::getline(std::cin, hex);
	std::string digest = getBytes(hex);

	std::string mask = "llllll";
	//std::cout << "Enter the mask (u/l/d): ";
	//std::getline(std::cin, mask);

	std::string threadsNum = "4";
	//std::cout << "Enter the number of threads: ";
	//std::getline(std::cin, threadsNum);

	Iterator iterator = Iterator(mask);

	std::vector<Iterator> jobs = iterator.divideWork(std::stoi(threadsNum));
	std::vector<std::thread> threads(jobs.size());
	
	start = std::chrono::high_resolution_clock::now();

	int threadID = 0;
	for (Iterator & iter : jobs) {
		std::thread th(cracker, std::ref(iter), digest, threadID++);
		threads.push_back(move(th));
	}

	while (!match) {
		spinner();
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}

	for (std :: thread & th : threads) {
		if (th.joinable())
			th.join();
	}

    return 0;
}