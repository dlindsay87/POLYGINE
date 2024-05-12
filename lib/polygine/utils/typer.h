#ifndef TYPER_H
#define TYPER_H

#include <chrono>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <thread>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::flush;
using std::setprecision;
using std::fixed;

typedef std::string str;
typedef std::vector<std::string> strvec;
typedef std::vector<float> fltvec;
typedef std::stringstream ss;
typedef const char cc;

typedef std::chrono::steady_clock sc;
typedef std::chrono::time_point<sc> tp_sc;
typedef std::chrono::duration<double> dd;

template<typename T>
str fill(int space, char fillStr, T a) {
	ss os;
	os << std::setw(space) << std::setfill(fillStr) << a;
	return os.str();
}

#endif
