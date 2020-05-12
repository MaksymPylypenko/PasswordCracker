#include "../CRYPTOPP_8_2_0/cryptlib.h"
#include "../CRYPTOPP_8_2_0/sha.h"
#include "../CRYPTOPP_8_2_0/hex.h"
#include "../CRYPTOPP_8_2_0/files.h"


std::string getBytes(std::string hex) {
	using namespace CryptoPP;
	std::string bytes;
	HexDecoder decoder;
	decoder.Put((byte*)hex.data(), hex.size());
	decoder.MessageEnd();
	word64 size = decoder.MaxRetrievable();
	if (size && size <= SIZE_MAX)
	{
		bytes.resize(size);
		decoder.Get((byte*)&bytes[0], bytes.size());
	}
	return bytes;
}


bool isMatch(std::string msg, std::string digest) {
	using namespace CryptoPP;	
	SHA256 hash;
	bool result;
	StringSource(digest + msg, true, new HashVerificationFilter(hash,
		new ArraySink((byte*)&result, sizeof(result))));
	return result;
}