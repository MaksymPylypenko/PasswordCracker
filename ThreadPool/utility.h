#ifndef util_h
#define util_h

#include <string>
#include <vector>


class Iterator {
public:
	Iterator(std::string mask, std::vector<int> offset);

	/// Allows to generate all possible combinations of a word with a fixed size.
	bool next(int rotor = 0);

	// Allows to generate all possible combinations of words with any size.
	bool guessWord();

	/// Holds a recently guessed word. 
	///
	/// Examples of lowercase words: "a", "aa", "baa", "caa", "zzz"    
	/// Examples of custom words: "0", "0aA", "4faasdXMMA" ...
	std::string word;

	/// Sets rotors depending on the number of [currDigits].
	///
	/// Rotors act like a set of clocks. When the 1st makes a full circle, it rotates the next one.
	/// For example, we start from single digit words [a], [b], [c] ... 
	/// When the last digit is reached e.g [z], rotors are reset to allow longer words: [a][a], [b][a] ... 
	/// Resets happen at [z][z], [z][z][z] etc.
	void resetRotors(); 

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

	/// Defines initial positions of the rotors.
	std::string start;

	/// Allows to bypass combinations that we don't need.
	std::vector<int> offset;
	
	/// Allows to limit rotations of rotors.
	std::vector<int> combinations; 			
};

#endif util_h