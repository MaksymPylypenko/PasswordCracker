#include "pch.h"

#include "../ThreadPool/iterator.cpp"


TEST(Combinations, twoDigits) {

	std::string mask = "ll";
	std::vector<int> offset(2, 0);

	Iterator iterator = Iterator(mask);
	iterator.init(offset);

	iterator.setLen(2);	


	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26 * 26);
	EXPECT_TRUE(true);
}


TEST(Combinations, threeDigits) {

	std::string mask = "lll";
	std::vector<int> offset(3,0);

	Iterator iterator = Iterator(mask);
	iterator.init(offset);

	iterator.setLen(2);


	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26 * 26);
	EXPECT_TRUE(true);
}


TEST(Combinations, offSet) {

	std::string mask = "ll";
	std::vector<int> offset(2, 13);

	Iterator iterator = Iterator(mask);
	iterator.init(offset);

	iterator.setLen(2);


	bool wordsLeft = true;
	int count = 0;
	while (wordsLeft) {
		count++;
		if (!iterator.next()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, (26 - 13) * (26 - 13));
	EXPECT_TRUE(true);
}