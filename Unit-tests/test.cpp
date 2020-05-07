#include "pch.h"

#include "../ThreadPool/iterator.cpp"


TEST(Charset, numbers) {
	std::string mask = "dd";
	Iterator iterator = Iterator(mask);
	iterator.currDigits = 2;
	iterator.resetRotors();

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}
	EXPECT_EQ(count, 10 * 10);

	int zero = iterator.word.compare(std::string(2, '9'));
	EXPECT_EQ(zero, 0);
}


TEST(Charset, numbers_and_letters) {
	std::string mask = "dl";
	Iterator iterator = Iterator(mask);
	iterator.currDigits = 2;
	iterator.resetRotors();

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}
	EXPECT_EQ(count, 10 * 26);

	int zero = iterator.word.compare(std::string{ "9z" });
	EXPECT_EQ(zero, 0);
}

TEST(Rotors, one) {
	std::string mask = "l";
	Iterator iterator = Iterator(mask);
	iterator.resetRotors();

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}
	
	EXPECT_EQ(count, 26);

	int zero = iterator.word.compare(std::string(1, 'z'));
	EXPECT_EQ(zero, 0);
}


TEST(Rotors, two) {
	std::string mask = "ll";
	Iterator iterator = Iterator(mask);
	iterator.currDigits = 2;
	iterator.resetRotors();

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}
	EXPECT_EQ(count, 26 * 26);

	int zero = iterator.word.compare(std::string(2, 'z'));
	EXPECT_EQ(zero, 0);
}


TEST(Rotors, three) {
	std::string mask = "lll";
	Iterator iterator = Iterator(mask);
	iterator.currDigits = 3;
	iterator.resetRotors();

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}
	EXPECT_EQ(count, 26 * 26 * 26);

	int zero = iterator.word.compare(std::string(3, 'z'));
	EXPECT_EQ(zero, 0);
}


TEST(Offset, start) {

	std::string mask = "ll";
	Iterator iterator = Iterator(mask);
	iterator.offsetStart = std::vector<int>(2, 13);
	iterator.currDigits = 2;
	iterator.resetRotors();

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26* (26 - 13) - 13);
}


TEST(Offset, end) {

	std::string mask = "ll";
	Iterator iterator = Iterator(mask);
	iterator.offsetBreak = std::vector<int>(2, 13);
	iterator.currDigits = 2;
	iterator.resetRotors();

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26 * (26 - 13) - 13);
}


TEST(Offset, range) {
	std::string mask = "dd";
	Iterator iterator = Iterator(mask);
	iterator.offsetStart = std::vector<int>(mask.size(), 5); 
	iterator.offsetBreak = std::vector<int>(mask.size(), 7); 
	iterator.currDigits = 2;
	iterator.resetRotors();

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 4*10 + 5);
}