#include "pch.h"

#include "../ThreadPool/iterator.cpp"


TEST(Combinations, oneRotor) {

	std::string mask = "l";
	std::vector<int> offset(1, 0);

	Iterator iterator = Iterator(mask, offset);
	iterator.currDigits = 1;
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
}


TEST(Combinations, twoRotors) {

	std::string mask = "ll";
	std::vector<int> offset(2, 0);

	Iterator iterator = Iterator(mask, offset);
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
}


TEST(Combinations, threeRotors) {

	std::string mask = "lll";
	std::vector<int> offset(3,0);

	Iterator iterator = Iterator(mask, offset);
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
}


TEST(Combinations, offSet) {

	std::string mask = "ll";
	std::vector<int> offset(2, 13);

	Iterator iterator = Iterator(mask, offset);
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