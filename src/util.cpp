#include "util.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <iostream>
#include <fstream>

bool Util::mkdir(std::string path){
	struct stat info;
	//make sure we have an assets directory
	int nError = 0;
	if (stat(path.c_str(), &info) != 0) {
#if defined(_WIN32)
		nError = _mkdir(path.c_str());
#else
		nError = mkdir(path.c_str(), 0733);
#endif
	} else if (info.st_mode & S_IFDIR) {
		std::cout << path <<" folder exists" << std::endl;
	} else {
#if defined(_WIN32)
		nError = _mkdir(path.c_str());
#else
		nError = mkdir(path.c_str(), 0733);
#endif
	}
	if (nError != 0) {
		std::cout << "Error Creating " << path << " Directory" << std::endl;
	}
	return nError;
}

std::string Util::md5hash(std::string message){
	byte digest[ CryptoPP::Weak::MD5::DIGESTSIZE ];

	CryptoPP::Weak::MD5 hash;
	hash.CalculateDigest( digest, (const byte*)message.c_str(), message.length() );

	CryptoPP::HexEncoder encoder;
	std::string output;

	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

bool Util::saveFile(std::string path, std::string content){
	std::ofstream f;
	f.open(path);
	f << content;
	f.close();
	return 0;
}

bool Util::invalidChar(char c) {
	return !(c>=0 && c <128);
}

void Util::sanitize(std::string & str){
	str.erase(remove_if(str.begin(),str.end(), invalidChar), str.end());
}
