#ifndef util_h
#define util_h

#include <string>
#include <vector>


class Iterator {
public:
	Iterator(std::string mask);
	void init(std::vector<int> offset);

	/// Examples of starting words  "aaa", "AAA"
	std::string start;      

	/// Examples of current words "baa", "caa", "zzz"
	std::string word;          

	/// Describes posible characters that each digit can have.
	/// For example, upper case letters [u], lower case letters [l] ...
	std::string mask;            

	/// Recursively iterates all possible combinations.
	bool next(int rotor = 0);	 

	/// The length of the current [word]
	void setLen(int digits);

	/// The Number of combinations for different lengths.
	std::vector<int> combinations;
	int id;
};

#endif util_h