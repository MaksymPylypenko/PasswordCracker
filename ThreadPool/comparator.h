#ifndef comparator_h
#define comparator_h

#include "../CRYPTOPP_8_2_0/cryptlib.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "../CRYPTOPP_8_2_0/md5.h"
#include "../CRYPTOPP_8_2_0/hex.h"
#include "../CRYPTOPP_8_2_0/files.h"


std::string getBytes(std::string hex);
bool isMatch(std::string msg, std::string hash);


#endif comparator_h