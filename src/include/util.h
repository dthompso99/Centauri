#pragma once
#ifndef util_H
#define util_H

#include <stdio.h>
#include <string>
#include <cstdio>
#include <iostream>
#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif


class Util {
public:
	static bool mkdir(std::string path);
	static std::string md5hash(std::string in);
	static bool saveFile(std::string path, std::string content);
	static void sanitize(std::string & str);
	static bool invalidChar(char c);
	static std::string stripHeaders(std::string in);
private:
	Util(){};
};
#endif
