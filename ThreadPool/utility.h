#ifndef util_h
#define util_h

#include <string>
#include <vector>
#include <optional>
#include <assert.h> 
#include <algorithm>
#include <map> 


class Iterator {
public:
	Iterator(std::string mask);

	/// Alternative constructor for convenience
	///
	/// Sets-up custom offsets & calls [resetRotors]
	/// Note, [offsetFinish] is not inclusive, but [offsetFinish] is!
	Iterator(std::string mask, std::vector<int> offsetStart, std::vector<int> offsetFinish);

	/// Allows to generate all possible combinations of a word with a fixed size.
	bool next(int rotor = 0);

	// Allows to generate all possible combinations of words with any size.
	bool guessWord();

	/// Increases the length of a word.
	///
	/// Rotors act like a set of clocks. When the 1st makes a full circle, it rotates the next one.
	/// For example, we start from single digit words [a], [b], [c] ... 
	/// When the last digit is reached e.g [z], rotors are reset to allow longer words: [a][a], [b][a] ... 
	/// Resets happen at [z][z], [z][z][z] etc.
	bool resetRotors();

	/// This is the value that rotors point at
	///
	/// Examples of lowercase words: "a", "aa", "baa", "caa", "zzz"    
	/// Examples of custom words: "0", "0aA", "4faasdXMMA" ...
	std::string word;

	// Setters for private values
	void setWordLen(int n);
	void setStart(std::vector<int> offset);
	void setFinish(std::vector<int> offset);

	// Debug related stuff
	void printRage();
	void debug();
	int count;		

	// Allows to assign multiple threads [N] to iterate portions of the plain-text space  
	std::vector<Iterator> divideWork(int N);


private:
	/// Indicates the edge rotor. 
	///
	/// When the slowest rotor is [z], the reset usually happens at the next rotation.
	int slowestRotor;

	/// Keeping track of the current [word] size.
	///
	/// Allows to to generate all possible combinations & all possible sizes
	int currDigits;
	int maxDigits;

	/// Describes the initial positions of rotors.
	/// 
	/// This is generated from [startOffset] and stays the same
	/// for different [word] sizes.
	std::string initWord;

	/// Describes possible values that a digit at a certain rotor can have.
	///
	/// For example 
	/// - "ddd" is a 1-3 digits numbers
	/// - "lll" is a 1-3 len words (lower case) 
	std::string mask;

	/// Descrives starting & end-1 positions of the rotors
	///
	/// This allows to bypass combinations that we don't need.
	std::vector<int> offsetStart;
	std::vector<int> offsetFinish;

	/// Describes the distance to a final position
	///
	/// Examples for digits (0-9): 
	/// - [1][0] = distance of 1 
	/// - [0][1] = distance of 10
	//  - [3][4] = distance of 4*10 + 3
	std::vector<int> rotationsLeft;
};

#endif util_h