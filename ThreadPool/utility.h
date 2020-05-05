#ifndef UTIL
#define UTIL

#include <string>


/// Recursively iterates all possible combinations
bool inc(std::string& word, std::string& mask, int index = 0);

/// Returns the initial string (e.g. "aaa" or "000")
std::string init(std::string mask);

#endif