#ifndef comparator_h
#define comparator_h

#include "../packages/cryptopp/cryptlib.h"
#include "../packages/cryptopp/sha.h"
#include "../packages/cryptopp/hex.h"
#include "../packages/cryptopp/files.h"


std::string getBytes(std::string hex);
bool isMatch(std::string msg, std::string hash);


#endif comparator_h