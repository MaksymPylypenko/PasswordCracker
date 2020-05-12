#include "pch.h"

#include "../brute-force/iterator.cpp"


/// Utility functions to make tests cleaner

int countWords(Iterator &iterator) {
	int count = 1;
	while (iterator.next()) {
		count++;		
	}
	return count;
}

Iterator quickSetup(char * mask) {
	std::string s(mask);
	Iterator iterator = Iterator(s);
	iterator.setWordLen(s.size());
	iterator.resetRotors();
	return iterator;
}


/// Tests
TEST(Charset, numbers) {
	Iterator iterator = quickSetup("dd");

	char first_c1 = iterator.word[0];
	char first_c2 = iterator.word[1];
	EXPECT_EQ(first_c1, '0');
	EXPECT_EQ(first_c2, '0');

	int count = countWords(iterator);
	EXPECT_EQ(count, 10 * 10);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, '9');
	EXPECT_EQ(last_c2, '9');
}

TEST(Charset, numbers_and_letters) {
	Iterator iterator = quickSetup("dl");

	char first_c1 = iterator.word[0];
	char first_c2 = iterator.word[1];
	EXPECT_EQ(first_c1, '0');
	EXPECT_EQ(first_c2, 'a');

	int count = countWords(iterator);
	EXPECT_EQ(count, 10 * 26);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, '9');
	EXPECT_EQ(last_c2, 'z');
}

TEST(Rotors, one) {
	Iterator iterator = quickSetup("l");

	char first_c1 = iterator.word[0];
	EXPECT_EQ(first_c1, 'a');

	int count = countWords(iterator);	
	EXPECT_EQ(count, 26);

	char last_c1 = iterator.word[0];
	EXPECT_EQ(last_c1, 'z');
}

TEST(Rotors, two) {
	Iterator iterator = quickSetup("ll");

	char first_c1 = iterator.word[0];
	char first_c2 = iterator.word[1];

	EXPECT_EQ(first_c1, 'a');
	EXPECT_EQ(first_c2, 'a');

	int count = countWords(iterator);
	EXPECT_EQ(count, 26 * 26);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, 'z');
	EXPECT_EQ(last_c2, 'z');
}


TEST(Rotors, three) {
	Iterator iterator = quickSetup("lll");

	char first_c1 = iterator.word[0];
	char first_c2 = iterator.word[1];
	char first_c3 = iterator.word[2];

	EXPECT_EQ(first_c1, 'a');
	EXPECT_EQ(first_c2, 'a');
	EXPECT_EQ(first_c3, 'a');

	int count = countWords(iterator);
	EXPECT_EQ(count, 26 * 26 * 26);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	char last_c3 = iterator.word[2];
	EXPECT_EQ(last_c1, 'z');
	EXPECT_EQ(last_c2, 'z');
	EXPECT_EQ(last_c3, 'z');
}


TEST(Offset, start) {
	std::string mask = "dd";
	Iterator iterator = Iterator(mask);
	iterator.setStart(std::vector<int>(mask.size(), 5)); 
	iterator.setWordLen(2);
	iterator.resetRotors();

	char first_c1 = iterator.word[0];
	char first_c2 = iterator.word[1];
	EXPECT_EQ(first_c1, '5');
	EXPECT_EQ(first_c2, '5');

	int count = countWords(iterator);
	EXPECT_EQ(count, 5*10 - 5);
	
	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, '9');
	EXPECT_EQ(last_c2, '9');
}

TEST(Offset, end) {

	std::string mask = "ll";
	Iterator iterator = Iterator(mask);
	iterator.setFinish(std::vector<int>(2, 13));
	iterator.setWordLen(2);
	iterator.resetRotors();

	char first_c1 = iterator.word[0];
	char first_c2 = iterator.word[1];
	EXPECT_EQ(first_c1, 'a');
	EXPECT_EQ(first_c2, 'a');

	int count = countWords(iterator);

	// [aa,al) = 13*26
	// [al,ll] = 14

	EXPECT_EQ(count, 13 * (26) + 13 + 1);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, 'n');
	EXPECT_EQ(last_c2, 'n');
}

TEST(Offset, end2) {

	std::string mask = "ddd";
	Iterator iterator = Iterator(mask);
	iterator.setFinish(std::vector<int>(mask.size(), 3));
	iterator.setWordLen(3);
	iterator.resetRotors();

	char first_c1 = iterator.word[0];
	char first_c2 = iterator.word[1];
	char first_c3 = iterator.word[2];
	EXPECT_EQ(first_c1, '0');
	EXPECT_EQ(first_c2, '0');
	EXPECT_EQ(first_c3, '0');

	int count = countWords(iterator);

	// [000,300) = 3*10*10
	// [300,330) = 3*10
	// [330,333] = 4

	EXPECT_EQ(count, 3*(10*10) + 3*(10) + 4);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	char last_c3 = iterator.word[1];
	EXPECT_EQ(last_c1, '3');
	EXPECT_EQ(last_c2, '3');
	EXPECT_EQ(last_c3, '3');
}

TEST(Offset, range) {
	std::string mask = "dd";
	Iterator iterator = Iterator(mask);
	iterator.setStart(std::vector<int>(mask.size(), 5)); 
	iterator.setFinish(std::vector<int>(mask.size(), 7));
	iterator.setWordLen(2);
	iterator.resetRotors();

	char first_c1 = iterator.word[0];
	char first_c2 = iterator.word[1];
	EXPECT_EQ(first_c1, '5');
	EXPECT_EQ(first_c2, '5');

	int count = countWords(iterator);

	// 55 --> 77 
	// [55,75) = 2*10
	// [75,77] = 3 

	EXPECT_EQ(count, 2*10 + 3);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, '7');
	EXPECT_EQ(last_c2, '7');
}

TEST(Bruteforce, all_combinations) {
	std::string mask = "dd";

	Iterator iterator = Iterator(mask);
	iterator.setStart(std::vector<int>(mask.size(), 5));
	iterator.setFinish(std::vector<int>(mask.size(), 7));
	iterator.resetRotors();

	char first_c1 = iterator.word[0];
	EXPECT_EQ(first_c1, '5');

	bool wordsLeft = true;
	int count = 1;
	while (wordsLeft) {
		count++;
		if (!iterator.guessWord()) {
			wordsLeft = false;
		}
	}

	// len = 1 --> [5,7] = 3
	// len = 2 --> [55,77] = 2*10 + 3
	// + 1 to include 0 

	EXPECT_EQ(count, 2*10 + 3 + 3 + 1);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, '7');
	EXPECT_EQ(last_c2, '7');
}


TEST(MultiThreading, division_of_work) {
	std::string mask = "ddd";

	Iterator iterator = Iterator(mask);
	std::vector<Iterator> jobs = iterator.divideWork(2);

	int numJobs = jobs.size();
	EXPECT_EQ(numJobs, 2);

	jobs[0].setWordLen(3);
	jobs[0].resetRotors();
	jobs[1].setWordLen(3);
	jobs[1].resetRotors();
	
	int countJob0 = countWords(jobs[0]);
	int countJob1 = countWords(jobs[1]);

	EXPECT_EQ(countJob0, 500);
	EXPECT_EQ(countJob1, 500);
}