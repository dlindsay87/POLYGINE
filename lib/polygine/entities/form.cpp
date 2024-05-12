#include "form.h"

Form::Form() {
  _memberMap["shape"] = &_shape;
  _memberMap["colors"] = &_colors;
}

template<typename T>
void Form::speakVector(str member) {
  T values = get<T>(member);
  if (values != T{}) {
    ss speech;
    speech << "I have " << member << " that are ";
    for (auto it = values.begin(); it != values.end() - 1; it++) {
      speech << *it;
      if (member != "shape") {
        if (it != values.end() - 2) {
          speech << ", ";
        } else speech << " and ";
      } else speech << " by ";
    }
    speech << values.back() << ".";
    cout << speech.str() << endl;
  }
}

template<typename T>
void Form::speakScalar(str member) {
  T value = get<T>(member);
  if (value != T{}) {
    cout << "I have a " << member << " that is " << value << "." << endl;
  }
}

template<typename T>
void Form::set(str member, const T value) {
  if (_memberMap.count(member)) {
    *static_cast<T*>(_memberMap[member]) = value;
  } else cerr << "Error: I have no form member " << member << "." << endl;
}

template<typename T>
T Form::get(str member) {
  if (_memberMap.count(member)) {
    T value = *static_cast<T*>(_memberMap[member]);
    if (value != T{}){
      return value;
    } else cerr << "Error: Form member " << member << " uninitialized." << endl;  
  } else cerr << "Error: I have no form member " << member << "." << endl;
  return T{};
}

template<typename T>
void Form::addToVec(str member, const T value, bool verbose) {
  if (_memberMap.count(member)) {
    auto ptr = static_cast<T*>(_memberMap[member]);
    ptr->insert(ptr->end(), value.begin(), value.end());
    if (verbose) {
      cout << "Now, ";
      speakVector<T>(member);
    }
  } else cerr << "Error: I have no form member " << member << "." << endl;
}

