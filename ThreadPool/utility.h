#ifndef util_h
#define util_h

#include <string>
#include <vector>
#include <optional>
#include <assert.h> 


class Iterator {
public:
	Iterator(std::string mask);

	/// Allows to generate all possible rotationsLeft of a word with a fixed size.
	bool next(int rotor = 0);

	// Allows to generate all possible rotationsLeft of words with any size.
	bool guessWord();

	/// Holds a recently guessed word. 
	///
	/// Examples of lowercase words: "a", "aa", "baa", "caa", "zzz"    
	/// Examples of custom words: "0", "0aA", "4faasdXMMA" ...
	std::string word;

	/// Increases the length of a word.
	///
	/// Rotors act like a set of clocks. When the 1st makes a full circle, it rotates the next one.
	/// For example, we start from single digit words [a], [b], [c] ... 
	/// When the last digit is reached e.g [z], rotors are reset to allow longer words: [a][a], [b][a] ... 
	/// Resets happen at [z][z], [z][z][z] etc.
	bool resetRotors();

	/// Indicates the edge rotor. 
	///
	/// From the previous example, when the slowest rotor is [z], the reset will happen.
	/// Unless we don't need a longer word. 
	int slowestRotor;

	/// Tells if we can increase the size of a word.
	int currDigits;
	int maxDigits;
		 
	/// Describes possible values that a digit at a certain rotor can have.
	std::string mask;  


	/// Allows to bypass rotationsLeft that we don't need.
	std::vector<int> offsetStart;
	std::vector<int> offsetBreak;

	/// Holds a string position generated from [offsetStart].
	std::string initWord;
	
	/// Allows to limit rotations of rotors.
	std::vector<int> rotationsLeft; 			

	// Allows to assign multiple threads [N] to iterate portions of the plain-text space  
	std::vector<Iterator> divideWork(int N);
};

#endif util_h