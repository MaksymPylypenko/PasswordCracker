#include "pch.h"

#include "../brute-force/iterator.cpp"


/// Utility functions to make tests cleaner

int countWords(Rotors &rotors) {
	int count = 1;
	while (rotors.next()) {
		count++;		
	}
	return count;
}

TEST(Rotors, one_digit) {
	std::vector<int> maxValues{ 9 };
	Rotors r = Rotors(maxValues);
	r.init();

	int start_1 = r.curValues[0];
	EXPECT_EQ(start_1, 0);

	int count = countWords(r);	
	EXPECT_EQ(count, 10);

	int end_1 = r.curValues[0];
	EXPECT_EQ(end_1, 9);
}


TEST(Rotors, two_digits) {
	std::vector<int> maxValues{ 9,9 };
	Rotors r = Rotors(maxValues);
	r.init();

	int start_1 = r.curValues[0];
	int start_2 = r.curValues[1];
	EXPECT_EQ(start_1, 0);
	EXPECT_EQ(start_2, 0);

	int count = countWords(r);
	EXPECT_EQ(count, 10*10);

	int end_1 = r.curValues[0];
	int end_2 = r.curValues[1];
	EXPECT_EQ(end_1, 9);
	EXPECT_EQ(end_2, 9);
}


TEST(Rotors, three_digits) {
	std::vector<int> maxValues{ 9,9,9 };
	Rotors r = Rotors(maxValues);
	r.init();

	int start_1 = r.curValues[0];
	int start_2 = r.curValues[1];
	int start_3 = r.curValues[2];
	EXPECT_EQ(start_1, 0);
	EXPECT_EQ(start_2, 0);
	EXPECT_EQ(start_3, 0);

	int count = countWords(r);
	EXPECT_EQ(count, 10 * 10 * 10);

	int end_1 = r.curValues[0];
	int end_2 = r.curValues[1];
	int end_3 = r.curValues[2];
	EXPECT_EQ(end_1, 9);
	EXPECT_EQ(end_2, 9);
	EXPECT_EQ(end_3, 9);
}


TEST(Rotors, long_rounds) {
	std::vector<int> maxValues{ 999,999 };
	Rotors r = Rotors(maxValues);
	r.init();

	int start_1 = r.curValues[0];
	int start_2 = r.curValues[1];
	EXPECT_EQ(start_1, 0);
	EXPECT_EQ(start_2, 0);

	int count = countWords(r);
	EXPECT_EQ(count, 1000 * 1000);

	int end_1 = r.curValues[0];
	int end_2 = r.curValues[1];
	EXPECT_EQ(end_1, 999);
	EXPECT_EQ(end_2, 999);
}


TEST(Rotors, short_range) {
	std::vector<int> maxValues{ 9,9 };
	Rotors r = Rotors(maxValues);

	std::vector<int> start{ 0,0 };
	std::vector<int> end{ 1,0 };
	r.initRange(start,end);

	int start_1 = r.curValues[0];
	int start_2 = r.curValues[1];
	EXPECT_EQ(start_1, 0);
	EXPECT_EQ(start_2, 0);

	int count = countWords(r);
	EXPECT_EQ(count, 2);

	int end_1 = r.curValues[0];
	int end_2 = r.curValues[1];
	EXPECT_EQ(end_1, 1);
	EXPECT_EQ(end_2, 0);
}


TEST(Rotors, medium_range) {
	std::vector<int> maxValues{ 9,9 };
	Rotors r = Rotors(maxValues);

	std::vector<int> start{ 5,5 };
	std::vector<int> end{ 7,7 };

	r.initRange(start, end);

	int start_1 = r.curValues[0];
	int start_2 = r.curValues[1];
	EXPECT_EQ(start_1, 5);
	EXPECT_EQ(start_2, 5);

	int count = countWords(r);
	EXPECT_EQ(count, 2*10 + 3);

	int end_1 = r.curValues[0];
	int end_2 = r.curValues[1];
	EXPECT_EQ(end_1, 7);
	EXPECT_EQ(end_2, 7);
}


TEST(Rotors, medium_range2) {
	std::vector<int> maxValues{ 9,9 };
	Rotors r = Rotors(maxValues);

	std::vector<int> start{ 5,5 };
	std::vector<int> end{ 9,9 };

	r.initRange(start, end);

	int start_1 = r.curValues[0];
	int start_2 = r.curValues[1];
	EXPECT_EQ(start_1, 5);
	EXPECT_EQ(start_2, 5);

	int count = countWords(r);
	EXPECT_EQ(count, 4 * 10 + 5);

	int end_1 = r.curValues[0];
	int end_2 = r.curValues[1];
	EXPECT_EQ(end_1, 9);
	EXPECT_EQ(end_2, 9);
}

TEST(Rotors, impossible_range) {
	std::vector<int> maxValues{ 9,9 };
	Rotors r = Rotors(maxValues);

	std::vector<int> start{ 7,7 };
	std::vector<int> end{ 5,5 };
	bool isPossible_1 = r.initRange(start, end);		
	EXPECT_EQ(isPossible_1, false);

	start = std::vector<int>{ 7,7 };
	end = std::vector<int>{ 6,7 };

	bool isPossible_2 = r.initRange(start, end);
	EXPECT_EQ(isPossible_2, false);
}


TEST(Rotors, work_slice) {
	std::vector<int> maxValues{ 9,9,9 };
	Rotors r = Rotors(maxValues);

	std::vector<Rotors> slices = r.slice(2);
	EXPECT_EQ(slices.size(), 2);

	// Checking starting values
	int start_0_1 = slices[0].curValues[0];
	int start_0_2 = slices[0].curValues[1];
	int start_0_3 = slices[0].curValues[2];
	EXPECT_EQ(start_0_1, 0);
	EXPECT_EQ(start_0_2, 0);
	EXPECT_EQ(start_0_3, 0);

	int start_1_1 = slices[1].curValues[0];
	int start_1_2 = slices[1].curValues[1];
	int start_1_3 = slices[1].curValues[2];
	EXPECT_EQ(start_1_1, 0);
	EXPECT_EQ(start_1_2, 0);
	EXPECT_EQ(start_1_3, 5);

	// Checking the number of words produced
	int count_0 = countWords(slices[0]);
	int count_1 = countWords(slices[1]);

	EXPECT_EQ(count_0, 500);
	EXPECT_EQ(count_1, 500);

	// Checking final values
	int end_0_1 = slices[0].curValues[0];
	int end_0_2 = slices[0].curValues[1];
	int end_0_3 = slices[0].curValues[2];
	EXPECT_EQ(end_0_1, 9);
	EXPECT_EQ(end_0_2, 9);
	EXPECT_EQ(end_0_3, 4);

	int end_1_1 = slices[1].curValues[0];
	int end_1_2 = slices[1].curValues[1];
	int end_1_3 = slices[1].curValues[2];
	EXPECT_EQ(end_1_1, 9);
	EXPECT_EQ(end_1_2, 9);
	EXPECT_EQ(end_1_3, 9);
}


TEST(Iterator, all_combinations) {
	std::string mask = "dd";

	Iterator iterator = Iterator(mask);
	iterator.init();

	char first_c1 = iterator.word[0];
	EXPECT_EQ(first_c1, '0');

	bool wordsLeft = true;
	int count = 1;
	while (wordsLeft) {
		count++;
		if (!iterator.guessWord()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 10*10 + 10);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, '9');
	EXPECT_EQ(last_c2, '9');
}


TEST(Iterator, mask) {
	std::string mask = "lu";

	Iterator iterator = Iterator(mask);
	iterator.init();

	char first_c1 = iterator.word[0];
	EXPECT_EQ(first_c1, 'a');

	bool wordsLeft = true;
	int count = 1;
	while (wordsLeft) {
		count++;
		if (!iterator.guessWord()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(count, 26 * 26 + 26);

	char last_c1 = iterator.word[0];
	char last_c2 = iterator.word[1];
	EXPECT_EQ(last_c1, 'z');
	EXPECT_EQ(last_c2, 'Z');
}


TEST(Iterator, bruteforce) {
	std::string mask = "ddd";

	Iterator iterator = Iterator(mask);
	std::vector<Iterator> jobs = iterator.divideWork(2);

	int numJobs = jobs.size();
	EXPECT_EQ(numJobs, 2);

	bool wordsLeft;
		
	wordsLeft = true;
	int countJob0 = 1;
	while (wordsLeft) {
		countJob0++;
		if (!jobs[0].guessWord()) {
			wordsLeft = false;
		}
	}

	wordsLeft = true;
	int countJob1 = 1;
	while (wordsLeft) {
		countJob1++;
		if (!jobs[1].guessWord()) {
			wordsLeft = false;
		}
	}

	EXPECT_EQ(countJob0, 4+50+500);
	EXPECT_EQ(countJob1, 4+50+500);
}