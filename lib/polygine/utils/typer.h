#ifndef TYPER_H
#define TYPER_H

#include <chrono>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <thread>
#include <iomanip>
#include <memory>

#include <SDL2/SDL.h>
#include <GL/glew.h>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::ios;
using std::ctime;
using std::flush;
using std::setprecision;
using std::fixed;

typedef std::string str;
typedef std::vector<std::string> strvec;
typedef std::vector<float> fltvec;
typedef std::vector<GLfloat> glfltvec;
typedef std::vector<GLuint> gluintvec;
typedef std::vector<int> intvec;
typedef std::stringstream ss;
typedef const char cc;

typedef std::chrono::steady_clock sc;
typedef std::chrono::system_clock sys_c;
typedef std::chrono::time_point<sc> tp_sc;
typedef std::chrono::duration<double> dd;

#endif
