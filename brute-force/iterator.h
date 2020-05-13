#ifndef iterator_h
#define iterator_h

#include <string>
#include <vector>
#include <assert.h> 

class Rotors {
public: 
	Rotors(std::vector<int> rounds);

	/// Rotors will start at [0][0][0] and end at rounds[x][y][z] 
	void init();

	/// Rotors will start at [offsetStart] and stop at [offsetBreak].
	bool initRange(std::vector<int> offsetStart, std::vector<int> offsetBreak);

	/// At this position the value is reset to 0 and the next rotor is rotated.
	///
	/// For example, if [9] is the round position at rotor [0], then [8][0][0] --> [9][0][0] --> [0][1][0]
	std::vector<int> maxValues;

	/// Current values
	std::vector<int> curValues;

	int digits;
		
	/// Initially the right-most rotor
	int head;

	/// When the [head] is rotated this is decreased
	///
	/// This allows to stop rotations when the left-most rotor reaches [0],
	/// instead of comparing current value to break value after every rotation.
	std::vector<int> rotationsLeft;

	/// Recursively rotates rotors by 1 starting with the left most rotor 
	bool next(int rotor = 0);

	// Allows to assign multiple threads [N] to iterate portions of the plain-text space  
	std::vector<Rotors> slice(int parts);
};


class Iterator {
public:
	Iterator(std::string mask);

	void init();
	void initCustom(std::vector<Rotors> sets);

	/// Describes possible values that a digit at a certain rotor can have.
	///
	/// For example 
	/// - "ddd" is a 1-3 digits numbers
	/// - "lll" is a 1-3 len words (lower case) 
	std::string mask;

	/// Holds different sets of rotors.
	///
	/// Allows to slice work equally between multiple threads for differnet word lengths.
	std::vector<Rotors> sets;
	int currSet;


	// Allows to generate all possible combinations of words with any size.
	bool guessWord();

	/// Returns the value that rotors point at
	///
	/// Examples of lowercase words: "a", "aa", "baa", "caa", "zzz"    
	/// Examples of custom words: "0", "0aA", "4faasdXMMA" ...
	std::string word;
	void updateWord();

	// Debug related stuff	
	void debug();
	int count;		

	std::vector<Iterator> divideWork(int N);
};

void printRange(std::vector<int> start, std::vector<int> end);

#endif iterator_h