#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <iostream>
#include <fstream>
#include <cstring>

using std::cout;
using std::cin;
using std::cerr;

using std::endl;

namespace UTIL {

	using std::ios;
	
	char* fileReader(const char* filePath, bool verbose = false);

	void fileSaver(const char* filePath, char* content, bool verbose = false);
	
}

#endif
