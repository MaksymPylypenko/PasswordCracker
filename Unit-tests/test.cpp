#include "pch.h"

#include "../ThreadPool/INC.cpp"


TEST(Combinations, twoDigits) {

	std::string word = "aa";

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!inc(word,0)) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26 * 26);
	EXPECT_TRUE(true);
}


TEST(Combinations, threeDigits) {

	std::string word = "aaa";

	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!inc(word, 0)) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26 * 26 * 26);
	EXPECT_TRUE(true);
}