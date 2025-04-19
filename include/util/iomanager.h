#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <cstring>
#include <fstream>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;

using std::endl;

namespace UTIL
{

using std::ios;

char *fileReader(const char *filePath, bool verbose = false);

void fileSaver(const char *filePath, char *content, bool verbose = false);

} // namespace UTIL

#endif
