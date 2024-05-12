#ifndef FORM_H
#define FORM_H

#include <map>
#include "utils/typer.h"

struct Form {
private:
  std::map<str, void*> _memberMap;

  fltvec _shape;
  strvec _colors;

public:
  Form();

  template<typename T>
  void speakVector(str member);

  template<typename T>
  void speakScalar(str member);

  template<typename T>
  void set(str member, const T value);

  template<typename T>
  T get(str member);

  template<typename T>
  void addToVec(str member, const T value, bool verbose = false);

};

#endif
