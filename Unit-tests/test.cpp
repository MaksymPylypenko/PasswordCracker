#include "pch.h"

#include "../ThreadPool/iterator.cpp"


/// Test routines

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

/// Offsets
/// ----------------------------------------------------------------

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
	EXPECT_EQ(count, 3*(10*10) + 3*(10) + 3 + 1);

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
	// This is 2 rounds per 10 digits + 2
	EXPECT_EQ(count, 2*10 + 2 + 1);

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

	// len 1 = 5 --> 7 = 3
	// len 2 = 55 --> 77 = 2*10 + 3
	EXPECT_EQ(count, 2*10 + 3 + 3 + 1);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, '7');
	EXPECT_EQ(last_c2, '7');
}