#include "pch.h"

#include "../ThreadPool/iterator.cpp"


TEST(Combinations, twoDigits) {

	std::string word = "aa";
	std::string mask = "ll";

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!inc(word,mask)) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26 * 26);
	EXPECT_TRUE(true);
}


TEST(Combinations, threeDigits) {

	std::string word = "aaa";
	std::string mask = "lll";

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!inc(word, mask)) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26 * 26 * 26);
	EXPECT_TRUE(true);
}